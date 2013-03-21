//
//  hmdb-common.hpp
//  hmdb
//
//  Created by Matsuki Hidenori on 3/14/13.
//
//

#ifndef hmdb_hmdb_common_h
#define hmdb_hmdb_common_h

#include <sqlite3.h>
#include "hmdb-buildenv.h"
#include "hmdb-platform.h"

#ifndef HMLog
#define HMLog(...)
#endif

#if HMDB_CXX_FEATURE_CXX_NULLPTR
#define HMDB_NULL nullptr
#else
namespace hmdb {
    const class {
    public:
        template<class T>
        operator T*() const { return 0; }
        template<class C, class T>
        operator T C::*() const { return 0; }
//        template<class T>
//        friend std::istream& operator>>(std::istream& is, T& s) { return is; }
//        template<class T>
//        friend std::ostream& operator<<(std::ostream& os, T const& s) { return os << "[NULL]"; }
    private:
        void operator&() const;
    } HMNull = {};
}
#define HMDB_NULL hmdb::HMNull
#endif

#endif
