//
//  MapCompileDef.h
//  GLMapLib2.0
//
//  Created by rain_os on 3/2/15.
//  Copyright (c) 2015 nopwang. All rights reserved.
//

#ifndef GLMapLib2_0_MapCompileDef_h
#define GLMapLib2_0_MapCompileDef_h

// Platform recognition
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#	define MAP_PLATFORM_WINDOWS
#elif defined(_WIN64) || defined(__WIN64__) || defined(WIN64)
#	define MAP_PLATFORM_WINDOWS
#elif defined(__APPLE_CC__)
//Device, simulator, both requiring OS version 4.0 or greater
#	if __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ >= 40000 || __IPHONE_OS_VERSION_MIN_REQUIRED >= 40000
#		define  MAP_PLATFORM_MAC_IOS
#	else
#		define  MAP_PLATFORM_MAC_OSX
#	endif
#elif defined(__ANDROID__)
#	define MAP_PLATFORM_ANDROID
#elif defined(linux) || defined(__linux) || defined(__linux__)
#	define MAP_PLATFORM_LINUX
#elif defined(__native_client__)
#	define MAP_PLATFORM_NACL
#else
#	error "Couldn't recognize platform"
#endif

// CPU architechture type recognition
#if defined(_M_X64) || defined(__x86_64__) || defined(__powerpc64__) || defined(__alpha__) || defined (__ia64__) || defined(__s390__) || defined(__s390x__)
#	define MAP_ARCH_64BIT
#elif defined(_M_ARM) || defined(__arm__)
#	define MAP_ARCH_ARM
#else
#	define MAP_ARCH_32BIT
#endif

#ifndef MAP_ANDROID
#define MAP_IOS
#endif

// Debug or release mode.
//#if defined(_DEBUG) || defined(DEBUG)
//#	define MAP_DEBUG
//#else
//#	define MAP_RELEASE
//#endif
#define MAP_RELEASE
// #define MAP_DEBUG

#ifdef MAP_IOS
#define map_printf(format,...) printf("" format"", ##__VA_ARGS__)
#else
#include <android/log.h>
#include <stdlib.h>
#define map_printf(format,...) __android_log_print(ANDROID_LOG_INFO, "Log", ""format"", ##__VA_ARGS__)
#endif

#ifdef MAP_DEBUG
#ifdef MAP_IOS
#define printf_debug(format,...) printf("FUNCTION:%s,  LINE:%d   " format"", __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define printf_debug(format,...) __android_log_print(ANDROID_LOG_INFO, "Log", "FUNCTION:%s,  LINE:%d "format"", __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
#endif
#else
#define printf_debug(format,...)
#endif

#ifdef MAP_DEBUG
#ifdef MAP_IOS
#define printf_if(e, format,...)    \
if (e)  \
{       \
    printf("FUNCTION:%s,  LINE:%d   " format"", __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);   \
}
#else
#define printf_if(e, format,...)    \
if (e)  \
{   \
__android_log_print(ANDROID_LOG_INFO, "Log", "FUNCTION:%s,  LINE:%d "format"", __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);   \
}
#endif
#else
#define printf_if(e, format,...)
#endif

// Assert
#if defined(MAP_DEBUG)

#ifdef MAP_IOS
#include <assert.h>
#define map_assert(e) assert(e)
#define assertmsg(e, format,...) {if (!(e)) map_printf("" format"", ##__VA_ARGS__); map_assert(e);}
#else           // MAP_ANDROID
#define map_assert(e)   \
if (!(e))           \
{                   \
__android_log_print(ANDROID_LOG_INFO, "Log", "FUNCTION:%s,  LINE:%d  assert failed!", __PRETTY_FUNCTION__, __LINE__);           \
*(int *)0 = 0;\
}
#define assertmsg(e, format,...)    \
if (!(e))           \
{                   \
__android_log_print(ANDROID_LOG_INFO, "Log", "FUNCTION:%s,  LINE:%d  assert failed! "format"", __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);	\
*(int *)0 = 0;\
}
#endif

#else           // MAP_RELEASE
#define map_assert(e)
#define assertmsg(e, format,...)
#endif

// namespace
#define namespace_tencentmap_begin      namespace tencentmap {
#define namespace_tencentmap_end        }
#define using_namespace_tencentmap      using namespace tencentmap;

#endif
