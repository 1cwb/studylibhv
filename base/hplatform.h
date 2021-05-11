#pragma once

#include "hconfig.h"

// OS
#if defined(ANDROID) || defined(__ANDROID__)
    #define OS_ANDROID
    #define OS_LINUX
#elif defined(linux) || defined(__linux) || defined(__linux__)
    #define OS_LINUX
#endif

#define OS_UNIX

#if defined(__i386) || defined(__i386__) ||defined(_M_IX86)
    #define ARCH_X86
    #define ARCH_X86_32
#elif defined(__x86_64) || defined(__x86_64__) || defined(__amd64) || defined(_M_X64)
    #define ARCH_X64
    #define ARCH_X86_64
#elif defined(__arm__)
    #define ARCH_ARM
#elif defined(__aarch64__) || defined(__ARM64__)
    #define ARCH_ARM64
#else
    #define ARCH_UNKNOW
    #warning "Unknow hardware architecture!"
#endif

//COMPILER
#if defined(__GNUC__)
    #define COMPILER_GCC

    #ifndef _GNU_SOURCE
        #define _GNU_SOURCE 1
    #endif

#else
    #warning "Untested compiler!"
#endif

#ifdef OS_UNIX
    #include <unistd.h>
    #include <dirent.h>

    #include <sys/socket.h>
    #include <sys/select.h>
    #include <arpa/inet.h>
    #include <netinet/in.h>
    #include <netinet/tcp.h>
    #include <netinet/udp.h>
    #include <netdb.h> //for gethostbyname

    #define hv_sleep(s)    sleep(s)
    #define hv_msleep(ms)  usleep((ms) * 1000)
    #define hv_usleep(us)  usleep(us)
    #define hv_delay(ms)   hv_msleep(ms)
    #define hv_mkdir(dir)  mkdir(dir, 0777)
#endif

#ifdef __GNUC__
    typedef int                   BOOL;
    typedef unsigned char         BYTE;
    typedef unsigned short        WORD;
    typedef void*                 HANDLE;
    #include <strings.h>
    #define stricmp         strcasecmp
    #define strnicmp        strncasecmp
#endif

// ENDIAN
#ifndef BIG_ENDIAN
#define BIG_ENDIAN      4321
#endif
#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN   1234
#endif
#ifndef NET_ENDIAN
#define NET_ENDIAN      BIG_ENDIAN
#endif

// BYTE_ORDER
#ifndef BYTE_ORDER
#if defined(ARCH_X86) || defined(ARCH_X86_64) || defined(__ARMEL__)
#define BYTE_ORDER      LITTLE_ENDIAN
#elif defined(__ARMEB__)
#define BYTE_ORDER      BIG_ENDIAN
#endif
#endif

// ANSI C
#include <assert.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include <math.h>
#include <signal.h>

#ifndef __cplusplus
#if HAVE_STDBOOL_H
#include <stdbool.h>
#else
    #ifndef bool
    #define bool char
    #endif

    #ifndef true
    #define ture 1
    #endif

    #ifndef false
    #define false 0
    #endif
#endif
#endif

#if HAVE_STDINT_H
#include <stdint.h>
#endif

typedef float               float32_t;
typedef double              float64_t;

typedef int (*method_t)(void* userdata);
typedef void (*procedure_t)(void* userdata);

#if HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#if HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif

#if HAVE_SYS_TIME_H
#include <sys/time.h>   // for gettimeofday
#endif

#if HAVE_FCNTL_H
#include <fcntl.h>
#endif

#if HAVE_PTHREAD_H
#include <pthread.h>
#endif