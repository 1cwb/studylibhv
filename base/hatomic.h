#pragma once

// c++11
#include <atomic>

using std::atomic_flag;
using std::atomic_long;

#define ATOMIC_FLAG_TEST_AND_SET(p)     ((p)->test_and_set())
#define ATOMIC_FLAG_CLEAR(p)            ((p)->clear())

#ifndef ATOMIC_FLAG_INIT
#define ATOMIC_FLAG_INIT        { 0 }
#endif

#ifndef ATOMIC_VAR_INIT
#define ATOMIC_VAR_INIT(value)  (value)
#endif

#ifndef ATOMIC_ADD
#define ATOMIC_ADD(p, n)    (*(p) += (n))
#endif

#ifndef ATOMIC_SUB
#define ATOMIC_SUB(p, n)    (*(p) -= (n))
#endif

#ifndef ATOMIC_INC
#define ATOMIC_INC(p)       ((*(p))++)
#endif

#ifndef ATOMIC_DEC
#define ATOMIC_DEC(p)       ((*(p))--)
#endif

typedef atomic_flag                 hatomic_flag_t;
#define HATOMIC_FLAG_INIT           ATOMIC_FLAG_INIT
#define hatomic_flag_test_and_set   ATOMIC_FLAG_TEST_AND_SET
#define hatomic_flag_clear          ATOMIC_FLAG_CLEAR

typedef atomic_long                 hatomic_t;
#define HATOMIC_VAR_INIT            ATOMIC_VAR_INIT
#define hatomic_add                 ATOMIC_ADD
#define hatomic_sub                 ATOMIC_SUB
#define hatomic_inc                 ATOMIC_INC
#define hatomic_dec                 ATOMIC_DEC

