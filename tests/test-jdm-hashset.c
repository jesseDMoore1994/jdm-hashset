#include "jdm-hashset.h"
#include <jdm-alloc.h>
#include <jdm-log.h>

static b8 test_jdm_hashset_create_destroy(void) {
  return JDM_TRUE;
}

int main() {
  jdm_log_init();
  if(test_jdm_hashset_create_destroy() != JDM_TRUE) {
    JDM_LOG_ERROR("Write tests here...");
    return 1;
  }
  jdm_log_cleanup();
}
