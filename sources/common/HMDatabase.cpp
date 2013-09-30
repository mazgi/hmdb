//
//  HMDatabase.cpp
//  hmdb
//
//  Created by Matsuki Hidenori on 3/5/13.
//
//

#include <unistd.h>
#include "hmdb-common.hpp"
#include "HMDatabase.hpp"
#include "HMError.hpp"

namespace hmdb {
    static const int CloseRetryLimit = 5;
    static const int ExecRetryLimit = 5;
#if SQLITE_VERSION_NUMBER >= 3005000
    HMDatabase::HMDatabase(const char *dbPath, int mode, const char *vfsName)
    :databasePath_(dbPath)
    , vfsName_(vfsName == NULL ? "" : vfsName)
    , cachedStatements_()
    {
        db_ = NULL;
        inTransaction_ = false;
        executingStatement_ = false;
        mode_.set(OpenReadOnly);
        if (mode & OpenReadWrite) {
            mode_.set(OpenReadWrite);
        }
        if (mode & OpenCreate) {
            mode_.set(OpenCreate);
        }
    }
#else /* } SQLITE_VERSION_NUMBER { */
    HMDatabase(const std::string dbPath)
    :databasePath_(dbPath)
    {

    }
#endif /* } SQLITE_VERSION_NUMBER */

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
#else /* } SQLITE_VERSION_NUMBER { */
        result = sqlite3_open(databasePath_.c_str(), &db_);
#endif /* } SQLITE_VERSION_NUMBER */
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

    bool HMDatabase::executeFormattedQueryForRead(HMError* &outError, HMRecordReader* &outRet, const char* format, va_list args)
    {
        // variables for parse query
        bool parseQuerySuccess = true;
        char* sql = NULL;
        char* readPosition = NULL;
        char* insertPosition = NULL;
        
        // variables for build statement
        bool buildStmtSuccess = true;
        HMError* buildStmtErr = HMDB_NULL;
        sqlite3_stmt* stmt = NULL;

        // variables for bind parameters
        bool bindParameterSuccess = true;
        int intValue = 0;
        double doubleValue = 0.0;
        char* textValue = NULL;
        int bindResult = 0;
        int replacementIndex = 0;
        int replacementCount = 0;

        // parse format
        //TODO: limit
        sql = (char*)calloc(strlen(format) + 1/* '\0' */, sizeof(char));
        if (!sql) {
            parseQuerySuccess = false;
            HMLog("parse query error! can not allocate memory.");
            goto cleanup;
        }
        
        readPosition = const_cast<char*>(format);
        insertPosition = sql;
        while (*readPosition) {
            if (*readPosition == '%') {
                readPosition++;
                switch (*readPosition) {
                    case 'd': /* fall through */
                    case 'f': /* fall through */
                    case 's': /* fall through */
                        *insertPosition++ = '?';
                        readPosition++;
                        break;
                    case '%': /* fall through */
                    default:
                        break;
                }
            }
            *insertPosition++ = *readPosition++;
        }
        *insertPosition = '\0';

        // load/build statement
        buildStmtSuccess = buildStatement(buildStmtErr, stmt, sql);
        if (!buildStmtSuccess) {
            HMLog("build statement error! (%s)", sql);
            goto cleanup;
        }

        // bind parameter values to statement
        replacementCount = sqlite3_bind_parameter_count(stmt);
        readPosition = const_cast<char*>(format);
        replacementIndex = 0;
        while(*readPosition){
            if (*readPosition == '%') {
                readPosition++;
                switch (*readPosition) {
                    case 'd':
                        intValue = va_arg(args, int);
                        bindResult = sqlite3_bind_int(stmt, ++replacementIndex, intValue);
                        break;
                    case 'f':
                        doubleValue = va_arg(args, double);
                        bindResult = sqlite3_bind_double(stmt, ++replacementIndex, doubleValue);
                        break;
                    case 's':
                        textValue = va_arg(args, char*);
                        if (textValue) {
                            bindResult = sqlite3_bind_text(stmt, ++replacementIndex, textValue, -1, SQLITE_TRANSIENT);
                        } else {
                            bindResult = sqlite3_bind_null(stmt, ++replacementIndex);
                        }
                        break;
                    case '%': /* fall through */
                    default:
                        break;
                }
                if (bindResult != SQLITE_OK) {
                    bindParameterSuccess = false;
                    HMLog("bind parameters error! (%s)", sql);
                    goto cleanup;
                }
            }
            readPosition++;
        }
        if (replacementCount != replacementIndex) {
            bindParameterSuccess = false;
            HMLog("bind parameters error! parameter count mismatch (%s)", sql);
            goto cleanup;
        }

        // execute statement
        outRet = new HMRecordReader(stmt);

    cleanup:
        free(sql);
        return parseQuerySuccess & buildStmtSuccess & bindParameterSuccess;
    }

}
