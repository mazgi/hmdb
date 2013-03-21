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
            HMLog("error opening! [code:%d, errcode:%d, errmsg:%s]",
                  result, sqlite3_extended_errcode(db_), sqlite3_errmsg(db_));
            return false;
        }
        return true;
    }

    bool HMDatabase::close()
    {
        if (!db_) {
            return true;
        }
        
        // close opened statements.
        sqlite3_stmt* stmt = NULL;
        while ((stmt = sqlite3_next_stmt(db_, stmt))) {
            sqlite3_finalize(stmt);
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
                    HMLog("error closing! [code:%d, errcode:%d, errmsg:%s]",
                          result, sqlite3_extended_errcode(db_), sqlite3_errmsg(db_));
                    break;
            }
            usleep(20);
        } while (++numberOfRetries < CloseRetryLimit);
        return false;
    }

    bool HMDatabase::buildStatement(HMError* &outError, sqlite3_stmt* &outStmt, const char* sql)
    {
        StatementMap::iterator it = cachedStatements_.find(sql);
        if (it != cachedStatements_.end()) {
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
//                        cachedStatements_[sql] = outStmt;
                        return true;
                    case SQLITE_BUSY:
                    case SQLITE_LOCKED:
                        HMLog("database is busy. [code:%d]", result);
                        break;
                    default:
                        HMLog("error build statement with sql(%s)! [code:%d, errcode:%d, errmsg:%s]",
                              sql,
                              result, sqlite3_extended_errcode(db_), sqlite3_errmsg(db_));
                        break;
                }
                usleep(20);
            } while (++numberOfRetries < ExecRetryLimit);
        }
        return false;
    }

    bool HMDatabase::step(HMError* &outError, sqlite3_stmt* &outStmt)
    {
        int numberOfRetries = 0;
        do {
            int result = sqlite3_step(outStmt);
            switch (result) {
                case SQLITE_ROW:
                    numberOfRetries--;
                    break;
                case SQLITE_OK:
                    return true;
                case SQLITE_DONE:
                    return true;
                case SQLITE_ERROR:
                case SQLITE_MISUSE:
                    //TODO: err
                    break;
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

    char* HMDatabase::demangle__(const char *mangledName, int &status)
    {
        return abi::__cxa_demangle(mangledName, NULL, 0, &status);
    }
}
