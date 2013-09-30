//
//  HMResultSet.cpp
//  hmdb
//
//  Created by Matsuki Hidenori on 3/5/13.
//
//

#include <unistd.h>
#include "hmdb-common.hpp"
#include "HMRecordSet.hpp"

namespace hmdb {
    static const int ExecRetryLimit = 5;
    HMRecordReader::HMRecordReader(sqlite3_stmt* &stmt)
    {
        stmt_ = stmt;
        const int columnCount = sqlite3_column_count(stmt_);
        fieldNames.resize(columnCount);
        for (int i = 0; i < columnCount; i++) {
            const char* columnName = sqlite3_column_name(stmt_, i);
            if (columnName) {
                fieldNames[i] = columnName;
            }
            HMLog("col[%d]:%s", i, fieldNames[i].c_str());
        }
    }
    bool HMRecordReader::next(HMError* &outError)
    {
        int numberOfRetries = 0;
        do {
            const int result = sqlite3_step(stmt_);
            switch (result) {
                case SQLITE_ROW:
                    //TODO: read record
                    return true;
                case SQLITE_DONE:
                    return false;
                case SQLITE_ERROR:
                case SQLITE_MISUSE:
                    //TODO: err
                    HMLog("error execute step! [code:%d]", result);
                    break;
                case SQLITE_BUSY:
                case SQLITE_LOCKED:
                    HMLog("database is busy. [code:%d]", result);
                    break;
                default:
                    HMLog("error execute step! [code:%d]", result);
                    break;
            }
            usleep(20);
        } while (++numberOfRetries < ExecRetryLimit);
        return false;
    }
}
