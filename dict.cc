#include <sstream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include "dict.h"
#include "dictglobal.h"

using Dict = std::unordered_map<std::string, std::string>;
using IdentifierType = unsigned long;

namespace jnp1 {

namespace {
    #ifdef NDEBUG
        const bool debug = false;
    #else
        const bool debug = true;
    #endif

    IdentifierType dictCounter = 0;

    std::map<IdentifierType, Dict>& dicts() {
        static std::map<IdentifierType, Dict> dicts;

        return dicts;
    }

    std::string parse_char_param(const char* param) {
        if (param != NULL) {
            std::string paramStr(param);
            return "\"" + paramStr + "\"";
        }
        else
            return "NULL";
    }

    void function_called_msg(std::string funcName,
                             std::string params) {
        if (debug)
            std::cerr << funcName << "(" << params << ")" << std::endl;
    }

    void dict_new_msg(IdentifierType id) {
        if (debug)
            std::cerr << "dict_new: dict " << id
                      << " has been created" << std::endl;
    }

    void dict_delete_success_msg(IdentifierType id) {
        if (debug)
            std::cerr << "dict_delete: dict " << id
                      << " has been deleted" << std::endl;
    }

    void dict_delete_error_msg() {
        if (debug)
            std::cerr << "dict_delete: an attempt to remove the Global Dictionary"
                      << std::endl;
    }

    void dict_description_msg(IdentifierType id) {
        if (debug) {
            if (id != dict_global())
                std::cerr << "dict " << id;
            else
                std::cerr << "the Global Dictionary";
        }
    }

    void dict_size_msg(IdentifierType id, size_t size) {
        if (debug) {
            std::cerr << "dict_size: ";

            dict_description_msg(id);

            std::cerr << " contains " << size << " element(s)" << std::endl;
        }
    }

    void dict_insert_global_dict_msg() {
        if (debug)
            std::cerr << "dict_insert: attempt to overfill the Global Dictionary" << std::endl;
    }

    void dict_insert_success_msg(IdentifierType id,
                                 std::string key,
                                 std::string value) {
        if (debug) {
            std::cerr << "dict_insert: ";

            dict_description_msg(id);

            std::cerr << ", the pair (" << key << ", " << value << ")"
                      << " has been inserted" << std::endl;
        }
    }

    void dict_insert_error_msg(IdentifierType id, std::string param) {
        if (debug)
            std::cerr << "dict_insert: dict " << id
                      << " an attempt to insert NULL " << param << std::endl;
    }

    void dict_not_found_msg(std::string funcName, IdentifierType id) {
        if (debug)
            std::cerr << funcName << ": dict " << id << " does not exist" << "\n";
    }

    void key_not_found_msg(std::string funcName,
                           IdentifierType id,
                           const char* key) {
        if (debug)
            std::cerr << funcName << ": dict " << id
                      << " does not contain the key \"" << key << "\"\n";
    }

    void key_removed_msg(std::string funcName,
                         IdentifierType id,
                         const char* key) {
        if (debug) {
            std::cerr << funcName << ": ";

            dict_description_msg(id);

            std::cerr << " , the key \"" << key
                      << "\" has been removed" << std::endl;
        }
    }

    void value_found_msg(std::string funcName,
                         IdentifierType id,
                         const char* key,
                         std::string value) {
        if (debug) {
            std::cerr << funcName << ": ";

            dict_description_msg(id);

            std::cerr << ", the key \"" << key
                      << "\" has the value \"" << value
                      << "\"" << std::endl;
        }
    }

    void dict_copied_msg(std::string funcName,
                         IdentifierType src_id,
                         IdentifierType dst_id) {
        if (debug) {
            std::cerr << funcName << ": ";

            dict_description_msg(src_id);

            std::cerr << " has been copied into ";

            dict_description_msg(dst_id);

            std::cerr << std::endl;
        }
    }

    void search_global_dict_msg(std::string funcName) {
        if (debug)
            std::cerr << funcName << ": looking up the Global Dictionary\n";
    }

    void dict_cleared_msg(std::string funcName, IdentifierType id) {
        if (debug) {
            std::cerr << funcName << ": ";

            dict_description_msg(id);

            std::cerr << " has been cleared" << std::endl;
        }
    }
}

IdentifierType dict_new() {
    function_called_msg("dict_new", "");
    dicts().insert(std::make_pair(dictCounter, Dict()));

    dict_new_msg(dictCounter);

    return dictCounter++;
}

void dict_delete(unsigned long id) {
    std::stringstream ss;
    ss << id;
    function_called_msg("dict_delete", ss.str());

    const auto dictionaryIt = dicts().find(id);

    if (dictionaryIt != dicts().end()) {
        if (id == dict_global())
            dict_delete_error_msg();
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

    const auto dictionaryIt = dicts().find(id);

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
    const std::string keyDescription = parse_char_param(key);
    const std::string valueDescription = parse_char_param(value);

    ss << id << ", " << keyDescription << ", " << valueDescription;

    function_called_msg("dict_insert", ss.str());

    const auto dictionaryIt = dicts().find(id);

    if (dictionaryIt != dicts().end()) {
        if (key == NULL)
            dict_insert_error_msg(id, "key");
        else if (value == NULL)
            dict_insert_error_msg(id, "value");
        else {
            IdentifierType globalDictId = dict_global();

            const std::string keyStr(key);
            const std::string valueStr(value);

            Dict& dict = dictionaryIt->second;
            auto dictIt = dict.find(keyStr);

            if (dictIt != dict.end())
                dictIt->second = valueStr;
            else if (id != globalDictId || 
                     dict_size(globalDictId) < MAX_GLOBAL_DICT_SIZE)
                dict.insert(std::make_pair(keyStr, valueStr));
            else {
                dict_insert_global_dict_msg();
                
                return;
            }

            dict_insert_success_msg(id, keyDescription, valueDescription);
        }
    }
    else
        dict_not_found_msg("dict_insert", id);
}

void dict_remove(IdentifierType id, const char* key) {
    if (key == NULL)
        return;

    const auto dictionaryIt = dicts().find(id);

    if (dictionaryIt != dicts().end()) {
        if (dictionaryIt->second.erase(key) > 0)
            key_removed_msg("dict_remove", id, key);
        else
            key_not_found_msg("dict_remove", id, key);
    }
    else
        dict_not_found_msg("dict_remove", id);
}

const char* dict_find(IdentifierType id, const char* key) {
    if (key == NULL)
        return NULL;

    const auto dictionaryIt = dicts().find(id);

    if (dictionaryIt != dicts().end()) {
        const Dict& dict = dictionaryIt->second;
        const auto stringIt = dict.find(key);

        if (stringIt != dict.end()) {
            const std::string value = stringIt->second;

            value_found_msg("dict_find", id, key, value);

            return value.c_str();
        }
        else
            key_not_found_msg("dict_find", id, key);
    }
    else
        dict_not_found_msg("dict_find", id);

    if (id != dict_global()) {
        search_global_dict_msg("dict_find");

        return dict_find(dict_global(), key);
    }

    return NULL;
}

void dict_clear(IdentifierType id) {
    const auto dictionaryIt = dicts().find(id);

    if (dictionaryIt != dicts().end()) {
        dictionaryIt->second.clear();

        dict_cleared_msg("dict_clear", id);
    }
    else
        dict_not_found_msg("dict_clear", id);
}

void dict_copy(IdentifierType src_id, IdentifierType dst_id) {
    if (src_id == dst_id)
        return;

    const auto srcDictionaryIt = dicts().find(src_id);
    const auto dstDictionaryIt = dicts().find(dst_id);

    if (srcDictionaryIt != dicts().end() &&
        dstDictionaryIt != dicts().end()) {
        Dict& srcDict = srcDictionaryIt->second;
        Dict& dstDict = dstDictionaryIt->second;

        const bool isGlobalDict = dst_id == dict_global();

        for (auto srcIt = srcDict.begin(); srcIt != srcDict.end(); ++srcIt) {
            std::string srcKey = srcIt->first;
            std::string srcValue = srcIt->second;
            auto dstIt = dstDict.find(srcKey);

            if (dstIt != dstDict.end())
                dstIt->second = srcValue;
            else if (!isGlobalDict || dstDict.size() < MAX_GLOBAL_DICT_SIZE)
                dstDict.insert(make_pair(srcKey, srcValue));
            else
                break;
        }

        dict_copied_msg("dict_copy", src_id, dst_id);
    }
    else if (srcDictionaryIt != dicts().end())
        dict_not_found_msg("dict_copy", src_id);
    else
        dict_not_found_msg("dict_copy", dst_id);
}

}