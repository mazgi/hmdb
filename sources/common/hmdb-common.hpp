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
#define HMDB_NULL NULL
#endif

#endif
