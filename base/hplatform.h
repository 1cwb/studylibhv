#pragma once

#include <unistd.h>
#include <dirent.h>

#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netdb.h> //for gethostbyname

#include <strings.h>

#define hv_sleep(s)    sleep(s)
#define hv_msleep(ms)  usleep((ms) * 1000)
#define hv_usleep(us)  usleep(us)
#define hv_delay(ms)   hv_msleep(ms)
#define hv_mkdir(dir)  mkdir(dir, 0777)

#define stricmp         strcasecmp
#define strnicmp        strncasecmp


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
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>   // for gettimeofday
#include <fcntl.h>
#include <pthread.h>

typedef float               float32_t;
typedef double              float64_t;

typedef int (*method_t)(void* userdata);
typedef void (*procedure_t)(void* userdata);
