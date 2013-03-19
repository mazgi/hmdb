//
//  HMResultSet.cpp
//  hmdb
//
//  Created by Matsuki Hidenori on 3/5/13.
//
//

#include "hmdb-common.h"
#include "HMRecordSet.hpp"

namespace hmdb {
    bool HMRecordSet::nextRow(HMError* &outError)
    {
        return false;
        
        int numberOfRetries = 0;
        do {
            int result = sqlite3_step(stmt_);
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
//            usleep(20);
        } while (++numberOfRetries < 0);
        return false;
    }
}
