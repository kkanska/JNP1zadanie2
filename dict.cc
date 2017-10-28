#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include "dict.h"
#include "dictglobal.h"

typedef std::unordered_map<std::string, std::string> Dict;
typedef unsigned long IdentificatorType;

// consider map<unsigned long, unordered_map>
// somehow initialize dictglobal dictionary
std::map<IdentificatorType, Dict> dictionaries;
IdentificatorType dictCounter = dict_global();

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

static void dict_not_found_msg(std::string funcName, IdentificatorType id) {
    std::cerr << funcName << ": dict " << id << " does not exist" << "\n";
}

static void key_not_found_msg(std::string funcName,
                              IdentificatorType id,
                              const char* key) {
    std::cerr << funcName << ": dict " << id 
              << " does not contain the key " << key << "\"\n";
}

static void key_removed_msg(std::string funcName,
                            IdentificatorType id,
                            const char* key) {
    std::cerr << funcName << ": dict " << id
              << ", the key \"" << key << "\" has been removed\n";
}

static void value_found_msg(std::string funcName,
                            IdentificatorType id,
                            const char* key,
                            std::string value) {
    std::cerr << funcName << ": dict " << id
              << ", the key \"" << key
              << "\" has the value \"" << value << "\"\n";
}

static void dict_copied_msg(std::string funcName,
                            IdentificatorType src_id,
                            IdentificatorType dst_id) {
    std::cerr << funcName << ": dict " << src_id
              << " has been copied into dict " << dst_id << "\n";
}

static void searching_global_dictionary_msg(std::string funcName) {
    std::cerr << funcName << ": looking up the Global Dictionary\n";
}

static void clear_msg(std::string funcName, IdentificatorType id) {
    std::cerr << funcName << ": dict " << id << " has been cleared\n";
}