#ifndef ACTIONS_EXECUTION_LIST_H
#define ACTIONS_EXECUTION_LIST_H

#include "Actions/InstanceHandle.h"

namespace Actions {
  namespace ExecutionList {
    uint16_t getCount();
    uint16_t create(InstanceHandle handle, uint8_t actionStateLength);
    InstanceHandle getInstanceHandle(uint16_t index);
    void* getActionState(uint16_t index);
    void remove(uint16_t index);
  }
}

#endif
