#include "dict.h"
#include "dictglobal.h"

namespace jnp1 {

const size_t MAX_GLOBAL_DICT_SIZE = 42;

unsigned long dict_global() {
    static auto id = dict_new();
    return id;
}

}
