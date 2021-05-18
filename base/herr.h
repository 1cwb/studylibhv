#pragma once

#include <errno.h>
#include "hexport.h"

#ifndef SYS_NERR
    #define SYS_NERR 133
#endif

//F(errcode, name, errmsg)
//[1, 133]
#define FOREACH_ERR_SYS(F)

//[1xx~5xx]
#define FOREACH_ERR_STATUS(F)

//[1XXX]
#define FOREACH_ERR_COMMON(F) \
    F(0,    OK,                "OK")            \
    F(1000, UNKNOW,         "Unknow error")     \
    \
    F(1001, NULL_PARAM,     "Null parameter")   \
    F(1002, NULL_POINTER,   "Null pointer")     \
    F(1003, NULL_DATA,      "Null data")        \
    F(1004, NULL_HANDLE,    "Null handle")      \
    \
    F(1011, INVALID_PARAM,      "Invalid parameter")    \
    F(1012, INVALID_POINTER,    "Invalid pointer")      \
    