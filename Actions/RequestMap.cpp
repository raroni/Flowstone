#include <assert.h>
#include "Actions/RequestMap.h"

namespace Actions {
  uint16_t RequestMap::getCount() const {
    return count;
  }

  InstanceHandle RequestMap::getHandle(uint8_t index) const {
    return handles[index];
  }

  const Request* RequestMap::getRequest(uint8_t index) const {
    return &requests[index];
  }

  void RequestMap::clear() {
    count = 0;
  }

  void RequestMap::remove(uint8_t index) {
    count--;
    handles[index] = handles[count];
    requests[index] = requests[count];
  }

  void RequestMap::unset(InstanceHandle handle) {
    uint8_t index;
    bool result = findIndex(handle, &index);
    if(result) {
      count--;
      handles[index] = handles[count];
      requests[index] = requests[count];
    }
  }

  bool RequestMap::findIndex(InstanceHandle handle, uint8_t *index) const {
    for(uint8_t i=0; i<count; ++i) {
      if(handles[i] == handle) {
        *index = i;
        return true;
      }
    }
    return false;
  }

  void RequestMap::set(InstanceHandle handle, const Request *request) {
    uint8_t index;
    bool result = findIndex(handle, &index);
    if(result) {
      requests[index] = *request;
    } else {
      assert(count != max);
      handles[count] = handle;
      requests[count] = *request;
      count++;
    }
  }
}
