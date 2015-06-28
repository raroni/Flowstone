#include <assert.h>
#include "Actions3/InstanceHandleSet.h"

namespace Actions3 {
  uint8_t InstanceHandleSet::getCount() const {
    return count;
  }

  InstanceHandle InstanceHandleSet::getHandle(uint8_t index) const {
    return handles[index];
  }

  void InstanceHandleSet::remove(uint8_t index) {
    count--;
    handles[index] = handles[count];
  }

  bool InstanceHandleSet::findIndex(InstanceHandle handle) const {
    for(uint8_t i=0; i<count; ++i) {
      if(handles[i] == handle) {
        return true;
      }
    }
    return false;
  }

  void InstanceHandleSet::insert(InstanceHandle handle) {
    bool result = findIndex(handle);
    if(!result) {
      assert(count != max);
      handles[count] = handle;
      count++;
    }
  }
}
