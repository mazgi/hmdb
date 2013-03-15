//
//  HMDatabase.hpp
//  hmdb
//
//  Created by Matsuki Hidenori on 3/5/13.
//
//

#ifndef __hmdb__HMDatabase__
#define __hmdb__HMDatabase__

#include "hmdb-common.h"
#include <iostream>

namespace hmdb {
    class HMError;
    class HMResultSet;

    class HMDatabase {
    public:
        typedef enum {
            OpenReadOnly,
            OpenReadWrite,
            OpenCreate,
            
            OpenModeKeyAll
        } OpenModeKey;
        typedef std::bitset<OpenModeKeyAll> OpenMode;
    private:
        std::string databasePath_;
        sqlite3 *db_;
#if SQLITE_VERSION_NUMBER >= 3005000
        std::string vfsName_;
        OpenMode mode_;
#endif
    public:
#if SQLITE_VERSION_NUMBER >= 3005000
        HMDatabase(const char *dbPath, int mode = OpenCreate|OpenReadWrite, const char *vfsName = NULL);
#else
        HMDatabase(const char *dbPath);
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
