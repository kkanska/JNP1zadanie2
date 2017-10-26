#ifndef __DICT_H__
#define __DICT_H__

unsigned long dict_new();

void dict_remove(unsigned long id, const char* key);

const char* dict_find(unsigned long id, const char* key);

void dict_clear(unsigned long id);

void dict_copy(unsigned long src_id, unsigned long dst_id);

#endif /* __DICT_H__ */
