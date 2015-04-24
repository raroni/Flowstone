#include <assert.h>
#include "Misc/IntegerPool.h"

uint16_t IntegerPool::obtain() {
  if(recycleCount == 0) {
    return max++;
  } else {
    recycleCount--;
    return recycles[recycleCount];
  }
}
void IntegerPool::release(uint16_t value) {
  assert(recycleCount != recycleMax);
  recycles[recycleCount++] = value;
}
