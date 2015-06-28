#ifndef ACTIONS3_INSTANCE_HANDLE_SET_H
#define ACTIONS3_INSTANCE_HANDLE_SET_H

#include "Actions3/InstanceHandle.h"

namespace Actions3 {
  class InstanceHandleSet {
  public:
    InstanceHandle getHandle(uint8_t index) const;
    void insert(InstanceHandle handle);
    uint8_t getCount() const;
    void remove(uint8_t index);
  private:
    bool findIndex(InstanceHandle handle) const;
    const static uint8_t max = 128;
    uint8_t count = 0;
    InstanceHandle handles[max];
  };
}

#endif
