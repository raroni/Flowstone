#ifndef PHYSICS_FREE_LIST
#define PHYSICS_FREE_LIST

#include <assert.h>

namespace Physics {
  class FreeList {
    uint8_t nexts[UINT8_MAX+1];
    uint8_t next = 0;
  public:
    FreeList() {
      for(uint8_t i=0; UINT8_MAX>i; i++) {
        nexts[i] = i+1;
      }
    }
    uint8_t obtain() {
      assert(next != UINT8_MAX);
      uint8_t value = next;
      next = nexts[next];
      return value;
    }
    void free(uint8_t value) {
      nexts[value] = next;
      next = value;
    }
  };
}

#endif
