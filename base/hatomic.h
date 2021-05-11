#pragma once

#ifdef __cplusplus
#include <atomic> 

using std::atomic_flag;
using std::atomic_long;

#define ATOMIC_FLAG_TEST_AND_SET(p)      ((p)->test_and_set())
#define ATOMIC_FLAG_CLEAR(p)             ((p)->clear())
#endif

#ifndef ATOMIC_FLAG_INIT
#define ATOMIC_FLAG_INIT      { 0 }
#endif

#ifndef ATOMIC_VAR_INIT
#define ATOMIC_VAR_INIT(value)      (value)
#endif

#ifndef ATOMIC_FLAG_TEST_AND_SET
#define ATOMIC_FLAG_TEST_AND_SET      atomic_flag_test_and_set
static inline bool atomic_flag_test_and_set(atomic_flag* p)
{
    bool ret = p->_Value;
    p->_Value = 1;
    return ret;
}
#endif

#ifndef ATOMIC_FLAG_CLEAR
#define ATOMIC_FLAG_CLEAR      atomic_flag_clear
static inline void atomic_flag_clear(atomic_flag* p)
{
    p->_Value = 0;
}
#endif

#ifndef ATOMIC_ADD
#define ATOMIC_ADD(p, n)      (*(p) += (n))
#endif

#ifndef ATOMIC_SUB
#define ATOMIC_SUB(p, n)      (*(p) -= (n))
#endif

#ifndef ATOMIC_INC
#define ATOMIC_INC(p)         ((*(p)) ++)
#endif

#ifndef ATOMIC_DEC
#define ATOMIC_DEC(p)         ((*(p)) --)
#endif

using hatomic_flag_t = atomic_flag;
#define HATOMIC_FLAG_INIT              ATOMIC_FLAG_INIT
#define hatomic_flag_test_and_set      ATOMIC_FLAG_TEST_AND_SET
#define hatomic_flag_clear             ATOMIC_FLAG_CLEAR

using hatomic_t = atomic_long;
#define HATOMIC_VAL_INIT               ATOMIC_VAR_INIT
#define hatomic_add                    ATOMIC_ADD
#define hatomic_sub                    ATOMIC_SUB
#define hatomic_inc                    ATOMIC_INC
#define hatomic_dec                    ATOMIC_DEC