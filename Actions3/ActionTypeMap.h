#ifndef ACTIONS3_ACTION_TYPE_MAP_H
#define ACTIONS3_ACTION_TYPE_MAP_H

#include "Actions3/ActionType.h"
#include "Actions3/InstanceHandle.h"

namespace Actions3 {
  class ActionTypeMap {
  public:
    uint16_t getCount() const;
    void set(InstanceHandle handle, ActionType type);
    void unset(InstanceHandle handle);
    void clear();
    InstanceHandle getHandle(uint8_t index) const;
    ActionType getActionType(uint8_t index) const;
    void remove(uint8_t index);
  private:
    bool findIndex(InstanceHandle handle, uint8_t *index) const;
    static const uint8_t max = 128;
    InstanceHandle handles[max];
    ActionType actionTypes[max];
    uint8_t count = 0;
  };
}

#endif
