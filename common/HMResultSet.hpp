//
//  HMResultSet.h
//  hmdb
//
//  Created by Matsuki Hidenori on 3/5/13.
//
//

#ifndef __hmdb__HMResultSet__
#define __hmdb__HMResultSet__

#include <iostream>

namespace hmdb {
    class HMDatabase;

    typedef std::basic_string<u_int8_t> blob;

    class HMResult {
        HMDatabase *db_;
    public:
        bool next();
        int intForColumn(const std::string columnName);
        int intForColumn(const int columnIndex);
        double doubleForColumn(const std::string columnName);
        double doubleForColumn(const int columnIndex);
        long longForColumn(const std::string columnName);
        long longForColumn(const int columnIndex);
        std::string stringForColumn(const std::string columnName);
        std::string stringForColumn(const int columnIndex);
        blob blobForColumn(const std::string columnName);
        blob blobForColumn(const int columnIndex);
    };
} /* endof namespace */

#endif /* defined(__hmdb__HMResultSet__) */
