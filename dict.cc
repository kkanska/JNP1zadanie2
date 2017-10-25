#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include "dict.h"

typedef std::unordered_map<std::string, std::string> Dict;
typedef unsigned long IdentificatorType;

// consider map<unsigned long, unordered_map>
std::map<IdentificatorType, Dict> dictionaries;
IdentificatorType dictCounter = 0;

IdentificatorType dict_new() {
    dictionaries.insert(std::pair<IdentificatorType, Dict>(++dictCounter, Dict()));

    return dictCounter;
}