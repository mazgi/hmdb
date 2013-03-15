//
//  HMDatabase.cpp
//  hmdb
//
//  Created by Matsuki Hidenori on 3/5/13.
//
//

#include <unistd.h>
#include "hmdb-common.h"
#include "HMDatabase.hpp"

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
        const int CloseRetryLimit = 5;
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
}
