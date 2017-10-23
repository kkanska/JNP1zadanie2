#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include "dict.h"

typedef std::unordered_map<std::string, std::string> dict;
typedef unsigned long identificatorType;

// consider map<unsigned long, unordered_map>
std::map<identificatorType, dict> dictionaries;
unsigned dictCounter = 0;

identificatorType dict_new() {
    dictionaries.insert(std::pair<identificatorType, dict>(++dictCounter, dict()));

    return dictCounter;
}
