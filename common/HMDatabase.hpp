//
//  HMDatabase.hpp
//  hmdb
//
//  Created by Matsuki Hidenori on 3/5/13.
//
//

#ifndef __hmdb__HMDatabase__
#define __hmdb__HMDatabase__

#include <iostream>

namespace hmdb {
    class HMError;
    class HMResultSet;

    class HMDatabase {
#if SQLITE_VERSION_NUMBER >= 3005000
        typedef enum {
            OpenReadOnly = SQLITE_OPEN_READONLY,
            OpenReadWrite = SQLITE_OPEN_READWRITE,
            OpenCreate = SQLITE_OPEN_CREATE,
        } OpenMode;
#endif
        std::string databasePath_;
    public:
        HMDatabase(const std::string dbPath);
#if SQLITE_VERSION_NUMBER >= 3005000
        HMDatabase(const std::string dbPath, OpenMode mode);
        HMDatabase(const std::string dbPath, OpenMode mode, void *vfs);
#endif
        ~HMDatabase();
        bool open();
        bool close();
        bool executeUpdate(HMError &outError, std::string sql, ...);
        HMResultSet *executeQuery(HMError &outError, std::string sql, ...);
        bool beginTransaction();
        bool commitTransaction();
        bool rollbackTransaction();
    };
} /* endof namespace */

#endif /* defined(__hmdb__HMDatabase__) */
