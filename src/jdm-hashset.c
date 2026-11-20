#include "jdm-hashset.h"
#include <jdm-log.h>

struct jdm_hashset_t {
  jdm_alloc_t *alloc;
  jdm_hashmap_t *map;
  s32 *static_val;
};

jdm_hashset_t *jdm_hashset_create(const jdm_hashset_config_t cfg) {
  if (!JDM_IS_ALIGNED(cfg.initial_capacity, 2)) {
    JDM_LOG_ERROR("Hashmap initial capacity must be power of two");
    return JDM_NULL;
  }
  jdm_hashset_t *s = jdm_alloc(cfg.alloc, sizeof(jdm_hashset_t));
  if (s == JDM_NULL) {
    JDM_LOG_ERROR("Error allocating hashset");
    return JDM_NULL;
  }

  jdm_hashmap_t *m = jdm_hashmap_create(cfg);
  if (s == JDM_NULL) {
    JDM_LOG_ERROR("Error allocating underlying hashmap for hashset");
    return JDM_NULL;
  }

  s->alloc = cfg.alloc;
  s->map = m;
  s->static_val = (s32 *)1;
  return s;
}

void jdm_hashset_destroy(jdm_hashset_t *set) {
  jdm_alloc_t *alloc = set->alloc;
  jdm_hashmap_destroy(set->map);
  jdm_free(alloc, set);
}

jdm_hashset_status_t jdm_hashset_add(jdm_hashset_t *set, u8 *elem) {
  return jdm_hashmap_add(set->map, elem, (u8*)set->static_val);
}

jdm_hashset_status_t jdm_hashset_remove(jdm_hashset_t *set, u8 *elem) {
  return jdm_hashmap_remove(set->map, elem, JDM_NULL);
}

void jdm_hashset_remove_all(jdm_hashset_t *set) {
  jdm_hashmap_remove_all(set->map);
}

b8 jdm_hashset_contains(jdm_hashset_t *set, u8 *elem) {
  return jdm_hashmap_contains_key(set->map, elem);
}

sz jdm_hashset_size(jdm_hashset_t *set) {
  return jdm_hashmap_size(set->map);
}

sz jdm_hashset_capacity(jdm_hashset_t *set) {
  return jdm_hashmap_capacity(set->map);
}

void jdm_hashset_for_each(jdm_hashset_t *set, jdm_hashset_for_each_func_t f) {
  jdm_hashmap_for_each_key(set->map, f);
}

jdm_hashset_iterator_t jdm_hashset_iterator_create(jdm_hashset_t *set) {
  return (jdm_hashset_iterator_t) {
    .it = jdm_hashmap_iterator_create(set->map)
  };
}

jdm_hashset_status_t jdm_hashset_iterator_next(jdm_hashset_iterator_t it,
                                               u8 **out) {
  jdm_hashmap_entry_t* e;
  jdm_hashset_status_t s = jdm_hashmap_iterator_next(it.it, &e);
  if(s != JDM_HASHMAP_OK) {
    return s;
  }
  if(out) {
    *out = e->key;
  }
  return JDM_HASHMAP_OK;
}

jdm_hashset_status_t jdm_hashset_iterator_remove(jdm_hashset_iterator_t it) {
  return jdm_hashmap_iterator_remove(it.it, NULL);
}
