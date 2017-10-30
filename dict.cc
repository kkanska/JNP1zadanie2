#include <iostream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include "dict.h"
#include "dictglobal.h"

#ifndef NDEBUG
    static const bool debug = false;
#else
    static const bool debug = true;
#endif

typedef std::unordered_map<std::string, std::string> Dict;
typedef unsigned long IdentificatorType;

static IdentificatorType dictCounter = dict_global();

static const std::map<IdentificatorType, Dict> init_dicts() {
    std::map<IdentificatorType, Dict> dicts;
    dicts.insert(std::pair<IdentificatorType, Dict>(dict_global(), Dict()));

    return dicts;
}

static std::map<IdentificatorType, Dict>& dicts() {
    static std::map<IdentificatorType, Dict> dicts = init_dicts();

    return dicts;
}

static std::string parse_char_param(const char* param) {
    if (param != NULL) {
        std::string paramStr(param);
        return "\"" + paramStr + "\"";
    }
    else
        return "NULL";
}

static void function_called_msg(std::string funcName,
                                std::string params) {
    if (debug)
        std::cerr << funcName << "(" << params << ")" << std::endl;
}

static void dict_new_msg(IdentificatorType id) {
    if (debug)
        std::cerr << "dict_new: dict " << id
                  << " has been created" << std::endl;
}

static void dict_delete_success_msg(IdentificatorType id) {
    if (debug)
        std::cerr << "dict_delete: dict " << id
                  << " has been deleted" << std::endl;
}

static void dict_delete_error_msg() {
    if (debug)
        std::cerr << "dict_delete: an attempt to remove the Global Dictionary"
                  << std::endl;
}

static void dict_description_msg(IdentificatorType id) {
    if (debug) {
        if (id != dict_global())
            std::cerr << "dict " << id;
        else
            std::cerr << "the Global Dictionary";
    }
}

static void dict_size_msg(IdentificatorType id, size_t size) {
    if (debug) {
        std::cerr << "dict_size: ";

        dict_description_msg(id);

        std::cerr << " contains " << size << " element(s)" << std::endl;
    }
}

static void dict_insert_success_msg(IdentificatorType id,
                                    std::string key,
                                    std::string value) {
    if (debug) {
        std::cerr << "dict_insert: ";

        dict_description_msg(id);

        std::cerr << ", the pair (" << key << ", " << value << ")"
                  << "has been inserted" << std::endl;
    }
}

static void dict_insert_error_msg(IdentificatorType id, std::string param) {
    if (debug)
        std::cerr << "dict_insert: dict " << id
                  << " an attempt to insert NULL " << param << std::endl;
}

static void dict_not_found_msg(std::string funcName, IdentificatorType id) {
    if (debug)
        std::cerr << funcName << ": dict " << id << " does not exist" << "\n";
}

static void key_not_found_msg(std::string funcName,
                              IdentificatorType id,
                              const char* key) {
    if (debug)
        std::cerr << funcName << ": dict " << id
                  << " does not contain the key " << key << "\"\n";
}

static void key_removed_msg(std::string funcName,
                            IdentificatorType id,
                            const char* key) {
    if (debug)
        std::cerr << funcName << ": dict " << id
                  << ", the key \"" << key << "\" has been removed\n";
}

static void value_found_msg(std::string funcName,
                            IdentificatorType id,
                            const char* key,
                            std::string value) {
    if (debug)
        std::cerr << funcName << ": dict " << id
                  << ", the key \"" << key
                  << "\" has the value \"" << value << "\"\n";
}

static void dict_copied_msg(std::string funcName,
                            IdentificatorType src_id,
                            IdentificatorType dst_id) {
    if (debug)
        std::cerr << funcName << ": dict " << src_id
                  << " has been copied into dict " << dst_id << "\n";
}

static void search_global_dict_msg(std::string funcName) {
    if (debug)
        std::cerr << funcName << ": looking up the Global Dictionary\n";
}

static void dict_cleared_msg(std::string funcName, IdentificatorType id) {
    if (debug)
        std::cerr << funcName << ": dict " << id << " has been cleared\n";
}

IdentificatorType dict_new() {
    function_called_msg("dict_new", "");
    dicts().insert(std::make_pair(++dictCounter, Dict()));

    dict_new_msg(dictCounter);

    return dictCounter;
}

void dict_delete(unsigned long id) {
    std::stringstream ss;
    ss << id;
    function_called_msg("dict_delete", ss.str());

    auto dictionaryIt = dicts().find(id);
    if (dictionaryIt != dicts().end()) {
        if (id == dict_global()) {
            dict_delete_error_msg();
        }
        else {
            dicts().erase(id);
            dict_delete_success_msg(id);
        }
    }
}

size_t dict_size(unsigned long id) {
    std::stringstream ss;
    ss << id;
    function_called_msg("dict_size", ss.str());

    auto dictionaryIt = dicts().find(id);
    if (dictionaryIt != dicts().end()) {
        size_t dictSize = dictionaryIt->second.size();

        dict_size_msg(id, dictSize);

        return dictSize;
    }
    else {
        dict_not_found_msg("dict_size", id);
        return 0;
    }
}

void dict_insert(unsigned long id, const char* key, const char* value) {
    std::stringstream ss;
    std::string keyDescription, valueDescription;

    keyDescription = parse_char_param(key);
    valueDescription = parse_char_param(value);
    ss << id << ", " << keyDescription << ", " << valueDescription;

    function_called_msg("dict_insert", ss.str());

    auto dictionaryIt = dicts().find(id);
    if (dictionaryIt != dicts().end()) {
        if (key == NULL) {
            dict_insert_error_msg(id, "key");
        }
        else if (value == NULL) {
            dict_insert_error_msg(id, "value");
        }
        else {
            // TODO: check if global dict (size constraint!)
            std::string keyStr(key);
            std::string valueStr(value);

            dictionaryIt->second.insert(std::make_pair(keyStr, valueStr));
            dict_insert_success_msg(id, keyDescription, valueDescription);
        }
    }
    else
        dict_not_found_msg("dict_insert", id);
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
