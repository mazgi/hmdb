//
//  hmdb-cocoa.h
//  hmdb
//
//  Created by Matsuki Hidenori on 3/14/13.
//
//

#ifndef hmdb_hmdb_cocoa_h
#define hmdb_hmdb_cocoa_h

#include "TargetConditionals.h"

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#endif

#include <sqlite3.h>
#ifdef HMLog
#undef HMLog
#endif
#define __BASENAME__ (strrchr(__FILE__, '/') + 1)
#define __HELPER_OF_HMLog(fmt, ...) NSLog(@"[%s:%05d](%s) " fmt "%s", __BASENAME__, __LINE__, __PRETTY_FUNCTION__, __VA_ARGS__)
//#define HMLog(...) __HELPER_OF_HMLog(__VA_ARGS__, "")
#endif

#ifdef TARGET_OS_IPHONE
// iOS
#elif TARGET_IPHONE_SIMULATOR
// iOS Simulator
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#else
// Unsupported platform
#endif
