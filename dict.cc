#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include "dict.h"

typedef std::unordered_map<std::string, std::string> Dict;
typedef unsigned long IdentificatorType;

// consider map<unsigned long, unordered_map>
// somehow initialize dictglobal dictionary
std::map<IdentificatorType, Dict> dictionaries;
IdentificatorType dictCounter = 0;

IdentificatorType dict_new() {
    dictionaries.insert(std::pair<IdentificatorType, Dict>(++dictCounter, Dict()));

    return dictCounter;
}

void dict_remove(IdentificatorType id, const char* key) {
    auto dictionaryIt = dictionaries.find(id);
    if (dictionaryIt != dictionaries.end()) {
        dictionaryIt->second.erase(key);
    }
}

const char* dict_find(IdentificatorType id, const char* key) {
    auto dictionaryIt = dictionaries.find(id);
    if (dictionaryIt != dictionaries.end()) {
        auto stringIt = dictionaryIt->second.find(key);
        if (stringIt != dictionaryIt->second.end()) {
            return stringIt->second.c_str();
        }
    }
    
    auto stringIt = dictionaries.at(0).find(key);
    if (stringIt != dictionaries.at(0).end()) {
        return stringIt->second.c_str();
    }

    return NULL;
}

void dict_clear(IdentificatorType id) {
    auto dictionaryIt = dictionaries.find(id);
    if (dictionaryIt != dictionaries.end()) {
        dictionaryIt->second.clear();
    }
}

void dict_copy(IdentificatorType src_id, IdentificatorType dst_id) {
    auto srcDictionaryIt = dictionaries.find(src_id);
    auto dstDictionaryIt = dictionaries.find(dst_id);
    if (srcDictionaryIt != dictionaries.end() &&
        dstDictionaryIt != dictionaries.end()) {
        // do not copy if destination dictionary is dictglobal and amount of keys exceeds size
        
        // copy contents
    }
}