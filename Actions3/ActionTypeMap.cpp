#include <assert.h>
#include <string.h>
#include "Actions3/ActionTypeMap.h"

namespace Actions3 {
  uint16_t ActionTypeMap::getCount() const {
    return count;
  }

  InstanceHandle ActionTypeMap::getHandle(uint8_t index) const {
    return handles[index];
  }

  ActionType ActionTypeMap::getActionType(uint8_t index) const {
    return actionTypes[index];
  }

  void ActionTypeMap::clear() {
    count = 0;
  }

  void ActionTypeMap::unset(InstanceHandle handle) {
    uint8_t index;
    bool result = findIndex(handle, &index);
    if(result) {
      count--;
      handles[index] = handles[count];
      actionTypes[index] = actionTypes[count];
    }
  }

  bool ActionTypeMap::findIndex(InstanceHandle handle, uint8_t *index) const {
    for(uint8_t i=0; i<count; ++i) {
      if(handles[i] == handle) {
        *index = i;
        return true;
      }
    }
    return false;
  }

  void ActionTypeMap::set(InstanceHandle handle, ActionType actionType) {
    uint8_t index;
    bool result = findIndex(handle, &index);
    if(result) {
      actionTypes[index] = actionType;
    } else {
      assert(count != max);
      handles[count] = handle;
      actionTypes[count] = actionType;
      count++;
    }
  }
}
