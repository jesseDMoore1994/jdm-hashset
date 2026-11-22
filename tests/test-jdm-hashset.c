#include "jdm-hashset.h"
#include <jdm-alloc.h>
#include <jdm-log.h>

typedef struct {
  jdm_alloc_t *test_alloc;
  jdm_hashset_t *test_set;
} test_ctx;

static test_ctx get_test_ctx(void) {
  jdm_alloc_t *alloc =
      jdm_alloc_create((jdm_alloc_config_t){.type = JDM_ALLOC_SYSTEM});
  jdm_hashset_t *set = jdm_hashset_create((jdm_hashset_config_t){
      .alloc = alloc,
      .load_factor = 0.75f,
      .initial_capacity = 16,
      .key_length = -1,
      .value_length = sizeof(s32),
      .hash_seed = 0,
      .hash = jdm_hashmap_hash_str,
      .key_compare = jdm_hashmap_str_key_compare,
  });
  return (test_ctx){
      .test_alloc = alloc,
      .test_set = set,
  };
}

static void destroy_test_ctx(test_ctx ctx) {
  jdm_hashset_destroy(ctx.test_set);
  jdm_alloc_destroy(ctx.test_alloc);
}

static b8 test_jdm_hashset_create_destroy(void) {
  test_ctx ctx = get_test_ctx();
  destroy_test_ctx(ctx);
  return JDM_TRUE;
}

static void log_elem(const u8 *k) { JDM_LOG_INFO("Elem '%s'", k); }

static b8 test_jdm_hashset_element_ops(void) {
  test_ctx ctx = get_test_ctx();
  jdm_alloc_t* alloc = ctx.test_alloc;
  jdm_hashset_t* set = ctx.test_set;

  jdm_hashset_add(set, "test");
  jdm_hashset_add(set, "foo");
  jdm_hashset_add(set, "bar");

  if(!jdm_hashset_contains(set, "test")) {
    JDM_LOG_ERROR("set should contain 'test'");
    destroy_test_ctx(ctx);
    return JDM_FALSE;
  }

  jdm_hashset_remove(set, "foo");
  if(jdm_hashset_contains(set, "foo")) {
    JDM_LOG_ERROR("set should not contain 'foo'");
    destroy_test_ctx(ctx);
    return JDM_FALSE;
  }
  if(jdm_hashset_size(set) != 2) {
    JDM_LOG_ERROR("set should have two elements");
    destroy_test_ctx(ctx);
    return JDM_FALSE;
  }
  if(jdm_hashset_capacity(set) != 16) {
    JDM_LOG_ERROR("set should have 16 slots");
    destroy_test_ctx(ctx);
    return JDM_FALSE;
  }
  jdm_hashset_for_each(set, log_elem);
  jdm_hashset_remove_all(set);
  if(jdm_hashset_size(set) != 0) {
    JDM_LOG_ERROR("set should have no elements");
    destroy_test_ctx(ctx);
    return JDM_FALSE;
  }

  destroy_test_ctx(ctx);
  return JDM_TRUE;
}

static b8 test_jdm_hashset_iterator(void) {
  test_ctx ctx = get_test_ctx();
  jdm_alloc_t* alloc = ctx.test_alloc;
  jdm_hashset_t* set = ctx.test_set;

  jdm_hashset_add(set, "test");
  jdm_hashset_add(set, "foo");
  jdm_hashset_add(set, "bar");

  jdm_hashset_iterator_t it = jdm_hashset_iterator_create(set);
  jdm_hashset_status_t s;
  char *elem = JDM_NULL;
  s = jdm_hashset_iterator_next(&it, (u8**)&elem);
  s = jdm_hashset_iterator_remove(&it);
  s = jdm_hashset_iterator_next(&it, (u8**)&elem);
  s = jdm_hashset_iterator_next(&it, (u8**)&elem);
  //
  if(jdm_hashset_size(set) != 2) {
    JDM_LOG_ERROR("set should have two elements");
    destroy_test_ctx(ctx);
    return JDM_FALSE;
  }
  if(jdm_hashset_contains(set, "foo")) {
    JDM_LOG_ERROR("foo should no longer be in set");
    destroy_test_ctx(ctx);
    return JDM_FALSE;
  }

  destroy_test_ctx(ctx);
  return JDM_TRUE;
}

int main() {
  jdm_log_init();
  if (test_jdm_hashset_create_destroy() != JDM_TRUE) {
    JDM_LOG_ERROR("test_jdm_hashset_create_destroy failed...");
    return 1;
  }
  if (test_jdm_hashset_element_ops() != JDM_TRUE) {
    JDM_LOG_ERROR("test_jdm_hashset_element_ops failed...");
    return 1;
  }
  if (test_jdm_hashset_iterator() != JDM_TRUE) {
    JDM_LOG_ERROR("test_jdm_hashset_iterator failed...");
    return 1;
  }
  jdm_log_cleanup();
}
