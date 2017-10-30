#ifndef __DICT_H__
#define __DICT_H__

#ifdef __cplusplus
extern "C" {
#endif

unsigned long dict_new();

void dict_delete(unsigned long id);

size_t dict_size(unsigned long id);

void dict_insert(unsigned long id, const char* key, const char* value);

void dict_remove(unsigned long id, const char* key);

const char* dict_find(unsigned long id, const char* key);

void dict_clear(unsigned long id);

void dict_copy(unsigned long src_id, unsigned long dst_id);

#ifdef __cplusplus
}
#endif

#endif /* __DICT_H__ */
