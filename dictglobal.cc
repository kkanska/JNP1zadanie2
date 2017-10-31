#include "dict.h"
#include "dictglobal.h"

const unsigned MAX_GLOBAL_DICT_SIZE = 42;

unsigned long dict_global() {
    static auto id = dict_new();
    return id;
}
