//
//  hmdb-android.h
//  hmdb
//
//  Created by Matsuki Hidenori on 3/14/13.
//
//

#ifndef hmdb_hmdb_android_h
#define hmdb_hmdb_android_h

#include <android/log.h>

#ifndef HMDB_PLATFORM
#define HMDB_PLATFORM_ANDROID
#define HMDB_PLATFORM "Android"
#endif

#define __BASENAME__ (strrchr(__FILE__, '/') + 1)
#define __HELPER_OF_HMLog(fmt, ...) \
__android_log_print(ANDROID_LOG_INFO, "hmdb", "[%s:%05d](%s) " fmt "%s\n", __BASENAME__, __LINE__, __PRETTY_FUNCTION__, __VA_ARGS__);
#define HMLog(...) __HELPER_OF_HMLog(__VA_ARGS__, "")

#endif /* defined(hmdb_hmdb_android_h) */
