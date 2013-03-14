//
//  hmdb-platform.h
//  hmdb
//
//  Created by Matsuki Hidenori on 3/14/13.
//
//

#ifndef hmdb_hmdb_platform_h
#define hmdb_hmdb_platform_h

#ifdef __APPLE__
#include "hmdb-cocoa.h"
#elif defined __ANDROID__
#include "hmdb-android.h"
#elif defined _WIN32 || defined _WIN64
#endif

#endif
