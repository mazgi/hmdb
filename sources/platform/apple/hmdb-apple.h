//
//  hmdb-apple.h
//  hmdb
//
//  Created by Matsuki Hidenori on 3/14/13.
//
//

#ifndef hmdb_hmdb_apple_h
#define hmdb_hmdb_apple_h

#include "TargetConditionals.h"

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#endif

#ifndef HMDB_PLATFORM
#   define HMDB_PLATFORM_APPLE
#   define HMDB_PLATFORM "Apple"
#endif

#ifdef HMDB_DEVELOP
#   define __BASENAME__ (strrchr(__FILE__, '/') + 1)
#   define __HELPER_OF_HMLog(fmt, ...) printf("[%s:%05d](%s) " fmt "%s\n", __BASENAME__, __LINE__, __PRETTY_FUNCTION__, __VA_ARGS__)
#   define HMLog(...) __HELPER_OF_HMLog(__VA_ARGS__, "")
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

#endif /* defined(hmdb_hmdb_apple_h) */
