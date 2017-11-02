#ifndef __DICTGLOBAL_H__
#define __DICTGLOBAL_H__

#include <stddef.h>

#ifdef __cplusplus
#include <iostream>

namespace jnp1 {
    extern "C" {
#endif

extern const size_t MAX_GLOBAL_DICT_SIZE;

unsigned long dict_global();

#ifdef __cplusplus
    };
}
#endif

#endif /* __DICTGLOBAL_H__ */
