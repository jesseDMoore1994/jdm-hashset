#ifndef JDM_HASHSET_H
#define JDM_HASHSET_H

#include <jdm-alloc.h>
#include <jdm-defs.h>

typedef enum {
    JDM_HASHSET_OK = 0,
    JDM_HASHSET_ERR_ALLOC
} jdm_hashset_status_t;

typedef struct jdm_hashset_t jdm_hashset_t;
typedef struct jdm_hashset_config_t jdm_hashset_config_t;

typedef void (*jdm_hashset_foreach_func_t)(const u8* elem);


jdm_hashset_t* jdm_hashset_create(const jdm_hashset_config_t* cfg);
void jdm_hashset_destroy(jdm_hashset_t* set);
jdm_hashset_status_t jdm_hashset_add(jdm_hashset_t* set, u8* elem);
jdm_hashset_status_t jdm_hashset_remove(jdm_hashset_t* set, u8* elem);
jdm_hashset_status_t jdm_hashset_remove_all(jdm_hashset_t* set);
b8 jdm_hashset_contains(jdm_hashset_t* set, u8* elem);
sz jdm_hashset_size(jdm_hashset_t* set);
sz jdm_hashset_capacity(jdm_hashset_t* set);
void jdm_hashset_foreach(jdm_hashset_t* set);

typedef struct {
    b8 dummy;
} jdm_hashset_iterator_t;

jdm_hashset_iterator_t jdm_hashset_iterator_create(jdm_hashset_t* set);
jdm_hashset_status_t jdm_hashset_iterator_next(jdm_hashset_iterator_t it, u8** out);
jdm_hashset_status_t jdm_hashset_iterator_remove(jdm_hashset_iterator_t it, u8** out);

#endif // JDM_HASHSET_H
