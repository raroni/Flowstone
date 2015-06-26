#ifndef ACTIONS3_EXECUTION_LIST_H
#define ACTIONS3_EXECUTION_LIST_H

#include "Actions3/InstanceHandle.h"

namespace Actions3 {
  namespace ExecutionList {
    uint16_t create(InstanceHandle handle, uint8_t actionStateLength);
    void* getActionState(uint16_t index);
    void remove(uint16_t index);
  }
}

#endif
