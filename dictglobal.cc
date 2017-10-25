#include "dictglobal.h"

#define DICT_GLOBAL_ID 0

const unsigned MAX_GLOBAL_DICT_SIZE = 42;

unsigned long dict_global() {
    return DICT_GLOBAL_ID;
}