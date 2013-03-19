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
    class HMError;
    class HMDatabase;
    
    typedef std::basic_string<u_int8_t> blob;

    class HMRecordSet {
        HMDatabase *db_;
        sqlite3_stmt *stmt_;
    public:
        bool nextRow(HMError* &outError);
        template<class T>
        const T& valueForColumnName(const char* name);
        template<class T>
        const T& valueForColumnIndex(const int index);

        
        int intForColumn(const char* columnName);
        int intForColumn(const int columnIndex);
        double doubleForColumn(const char* columnName);
        double doubleForColumn(const int columnIndex);
        long longForColumn(const char* columnName);
        long longForColumn(const int columnIndex);
        std::string stringForColumn(const char* columnName);
        std::string stringForColumn(const int columnIndex);
        blob blobForColumn(const char* columnName);
        blob blobForColumn(const int columnIndex);
    };
} /* endof namespace */

#endif /* defined(__hmdb__HMResultSet__) */
