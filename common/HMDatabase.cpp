//
//  HMDatabase.cpp
//  hmdb
//
//  Created by Matsuki Hidenori on 3/5/13.
//
//

#include <unistd.h>
#include <cxxabi.h>
#include "hmdb-common.h"
#include "HMDatabase.hpp"
#include "HMError.hpp"

namespace hmdb {
#if SQLITE_VERSION_NUMBER >= 3005000
    HMDatabase::HMDatabase(const char *dbPath, int mode, const char *vfsName)
    :databasePath_(dbPath), vfsName_(vfsName == NULL ? "" : vfsName)
    {
        mode_.set(OpenReadOnly);
        if (mode & OpenReadWrite) {
            mode_.set(OpenReadWrite);
        }
        if (mode & OpenCreate) {
            mode_.set(OpenCreate);
        }
    }
#else
    HMDatabase(const std::string dbPath)
    :databasePath_(dbPath)
    {

    }
#endif

    HMDatabase::~HMDatabase()
    {
        
    }

    bool HMDatabase::open()
    {
        if (db_) {
            return true;
        }

        int result = SQLITE_ANY;
#if SQLITE_VERSION_NUMBER >= 3005000
        int flag = SQLITE_OPEN_READONLY;
        if (mode_[OpenReadWrite]) {
            flag = SQLITE_OPEN_READWRITE;
        }
        if (mode_[OpenCreate]) {
            flag |= SQLITE_OPEN_CREATE;
        }
        const char *vfsName = NULL;
        if (!vfsName_.empty()) {
            vfsName = vfsName_.c_str();
        }
        result = sqlite3_open_v2(databasePath_.c_str(), &db_, flag, vfsName);
#else
        result = sqlite3_open(databasePath_.c_str(), &db_);
#endif
        if (result != SQLITE_OK) {
            HMLog("error opening! [code:%d]", result);
            return false;
        }
        return true;
    }

    bool HMDatabase::close()
    {
        if (!db_) {
            return true;
        }
        int numberOfRetries = 0;
        do {
            int result = sqlite3_close(db_);
            switch (result) {
                case SQLITE_OK:
                    db_ = NULL;
                    return true;
                case SQLITE_BUSY:
                case SQLITE_LOCKED:
                    HMLog("database is busy. [code:%d]", result);
                    break;
                default:
                    HMLog("error closing! [code:%d]", result);
                    break;
            }
            usleep(20);
        } while (++numberOfRetries < CloseRetryLimit);
        return false;
    }

    bool HMDatabase::buildStatement(HMError* &outError, sqlite3_stmt* &outStmt, const char* sql)
    {
        StatementMap::iterator it = cachedStatements_.find(sql);
        if (it == cachedStatements_.end()) {
            // use cached statement
            outStmt = it->second;
            sqlite3_reset(outStmt);
        }

        if (!outStmt) {
            int numberOfRetries = 0;
            do {
                int result = sqlite3_prepare_v2(db_, sql, -1, &outStmt, NULL);
                switch (result) {
                    case SQLITE_OK:
                        return true;
                    case SQLITE_BUSY:
                    case SQLITE_LOCKED:
                        HMLog("database is busy. [code:%d]", result);
                        break;
                    default:
                        HMLog("error build statement! [code:%d]", result);
                        break;
                }
                usleep(20);
            } while (++numberOfRetries < ExecRetryLimit);
        }
        return false;
    }

    void bindArgs(sqlite3_stmt *&stmt, const int replacementCount, int &index)
    {
        return;
    }
    template<class First>
    void bindArgs(sqlite3_stmt *&stmt, const int replacementCount, int &index, const First &value)
    {
        const char *CharArrayName = "char [";
        int status = 0;
        char *demangled = abi::__cxa_demangle(typeid(value).name(), NULL, 0, &status);
        if (status == 0) {
            if (strncmp(CharArrayName, demangled, strlen(CharArrayName)) == 0) {
//                const char *str = "";
//                sqlite3_bind_text(*stmt, 0, str, 0, NULL);
                std::cout <<
                value << "is char array"
                << std::endl;
            }
        }
        free(demangled);
    }
    template<class First, class ... Rest>
    void bindArgs(sqlite3_stmt *&stmt, const int replacementCount, int &index, const First &first, const Rest & ... rest)
    {
        bindArgs(stmt, replacementCount, index, first);
        bindArgs(stmt, replacementCount, index, rest ...);
    }
}
