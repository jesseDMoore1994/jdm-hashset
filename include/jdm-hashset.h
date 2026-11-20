#ifndef JDM_HASHSET_H
#define JDM_HASHSET_H

#include <jdm-alloc.h>
#include <jdm-defs.h>
#include <jdm-hashmap.h>

typedef jdm_hashmap_status_t jdm_hashset_status_t;
typedef struct jdm_hashset_t jdm_hashset_t;
typedef jdm_hashmap_config_t jdm_hashset_config_t;
typedef jdm_hashmap_for_each_key_func_t jdm_hashset_for_each_func_t;

jdm_hashset_t *jdm_hashset_create(const jdm_hashset_config_t cfg);
void jdm_hashset_destroy(jdm_hashset_t *set);
jdm_hashset_status_t jdm_hashset_add(jdm_hashset_t *set, u8 *elem);
jdm_hashset_status_t jdm_hashset_remove(jdm_hashset_t *set, u8 *elem);
void jdm_hashset_remove_all(jdm_hashset_t *set);
b8 jdm_hashset_contains(jdm_hashset_t *set, u8 *elem);
sz jdm_hashset_size(jdm_hashset_t *set);
sz jdm_hashset_capacity(jdm_hashset_t *set);
void jdm_hashset_for_each(jdm_hashset_t *set, jdm_hashset_for_each_func_t f);

typedef struct {
  jdm_hashmap_iterator_t it;
} jdm_hashset_iterator_t;

jdm_hashset_iterator_t jdm_hashset_iterator_create(jdm_hashset_t *set);
jdm_hashset_status_t jdm_hashset_iterator_next(jdm_hashset_iterator_t it,
                                               u8 **out);
jdm_hashset_status_t jdm_hashset_iterator_remove(jdm_hashset_iterator_t it);

#endif // JDM_HASHSET_H
