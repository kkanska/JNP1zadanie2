#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include "dict.h"
#include "dictglobal.h"

typedef std::unordered_map<std::string, std::string> Dict;
typedef unsigned long IdentificatorType;

// hide the counter
IdentificatorType dictCounter = dict_global();

static const std::map<IdentificatorType, Dict> init_dicts() {
    std::map<IdentificatorType, Dict> dicts;
    dicts.insert(std::pair<IdentificatorType, Dict>(dict_global(), Dict()));

    return dicts;
}

static std::map<IdentificatorType, Dict>& dicts() {
    static std::map<IdentificatorType, Dict> dicts = init_dicts();

    return dicts;
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

static void search_global_dict_msg(std::string funcName) {
    std::cerr << funcName << ": looking up the Global Dictionary\n";
}

static void dict_cleared_msg(std::string funcName, IdentificatorType id) {
    std::cerr << funcName << ": dict " << id << " has been cleared\n";
}

IdentificatorType dict_new() {
    dicts().insert(std::pair<IdentificatorType, Dict>(++dictCounter, Dict()));

    return dictCounter;
}

void dict_remove(IdentificatorType id, const char* key) {
    auto dictionaryIt = dicts().find(id);
    if (dictionaryIt != dicts().end()) {
        if (dictionaryIt->second.erase(key) > 0) {
            key_removed_msg("dict_remove", id, key);
        }
        else {
            key_not_found_msg("dict_remove", id, key);
        }
    } 
    else {
        dict_not_found_msg("dict_remove", id);
    }
}

const char* dict_find(IdentificatorType id, const char* key) {
    auto dictionaryIt = dicts().find(id);
    if (dictionaryIt != dicts().end()) {
        auto stringIt = dictionaryIt->second.find(key);
        if (stringIt != dictionaryIt->second.end()) {
            value_found_msg("dict_find", id, key, stringIt->second);

            return stringIt->second.c_str();
        }
        else {
            key_not_found_msg("dict_find", id, key);
        }
    }
    else {
        dict_not_found_msg("dict_find", id);
    }
    
    search_global_dict_msg("dict_find");
    
    auto stringIt = dicts().at(dict_global()).find(key);
    if (stringIt != dicts().at(dict_global()).end()) {
        value_found_msg("dict_find", dict_global(), key, stringIt->second);

        return stringIt->second.c_str();
    }
    else {
        key_not_found_msg("dict_find", dict_global(), key);
    }

    return NULL;
}

void dict_clear(IdentificatorType id) {
    auto dictionaryIt = dicts().find(id);
    if (dictionaryIt != dicts().end()) {
        dict_cleared_msg("dict_clear", id);

        dictionaryIt->second.clear();
    }
    else {
        dict_not_found_msg("dict_clear", id);
    }
}

void dict_copy(IdentificatorType src_id, IdentificatorType dst_id) {
    auto srcDictionaryIt = dicts().find(src_id);
    auto dstDictionaryIt = dicts().find(dst_id);
    if (srcDictionaryIt != dicts().end() &&
        dstDictionaryIt != dicts().end()) {
        // do not copy if destination dictionary is dictglobal and amount of keys exceeds size
        
        // copy contents
    }
}