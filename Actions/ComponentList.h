#ifndef ACTIONS_COMPONENT_LIST_H
#define ACTIONS_COMPONENT_LIST_H

#include "Actions/ComponentHandle.h"
#include "Actions/ActionStateHandle.h"
#include "Actions/Status.h"
#include "Actions/Request.h"

namespace Actions {
  namespace ComponentList {
    ComponentHandle create();
    uint16_t getIndex(ComponentHandle handle);
    const Request* getActiveRequest(uint16_t index);
    Status getStatus(uint16_t index);
    void updateActiveRequest(uint16_t index, const Request *request);
    void updateStateHandle(uint16_t componentIndex, ActionStateHandle stateHandle);
    void updateStatus(uint16_t index, Status status);
  }
}

#endif
