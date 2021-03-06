#pragma once

//HV_EXPORT
#if defined(HV_STATICLIB) || defined(HV_SOURCE)
    #define HV_EXPORT
#elif defined(__GNUC__)
    #define HV_EXPORT __attribute__((visibility("default")))
#else
    #define HV_EXPORT
#endif

//HV_DEPRECATED
#if defined(HV_NO_DEPRECATED)
    #define HV_DEPRECATED
#elif defined(__GNUC__) || defined(__clang__)
    #define HV_DEPRECATED __attribute__((deprecated))
#else
    #define HV_DEPRECATED
#endif

//HV_UNUSED
#if defined(__GNUC__)
    #define HV_UNUSED __attribute__(("unused"))
#else
    #define HV_UNUSED
#endif

// @param[IN | OUT | INOUT]
#ifndef IN
    #define IN
#endif

#ifndef OUT
    #define OUT
#endif

#ifndef INOUT
    #define INOUT
#endif

//@field[OPTIONAL | REQUIRED | REPEATED]
#ifndef OPTIONAL
    #define OPTIONAL
#endif

#ifndef REQUIRED
    #define REQUIRED
#endif

#ifndef REPEATED
    #define REPEATED
#endif

#ifndef BEGIN_NAMESPACE
    #define BEGIN_NAMESPACE(ns)    namespace ns {
#endif

#ifndef END_NAMESPACE
    #define END_NAMESPACE(ns)    } //namespace
#endif

#ifndef USING_NAMESPACE
    #define USING_NAMESPACE(ns) using namespace ns
#endif

#ifndef DEFAULT
    #define DEFAULT(x) = x
#endif

#ifndef ENUM
    #define ENUM(e)    enum e
#endif

#ifndef STRUCT
    #define STRUCT(s)    struct s
#endif

#define BEGIN_NAMESPACE_HV    BEGIN_NAMESPACE(hv)
#define END_NAMESPACE_HV      END_NAMESPACE(hv)
#define USING_NAMESPACE_HV    USING_NAMESPACE(hv)
