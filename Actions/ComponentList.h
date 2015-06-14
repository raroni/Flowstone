#ifndef ACTIONS_COMPONENT_LIST_H
#define ACTIONS_COMPONENT_LIST_H

#include "Actions/ComponentHandle.h"
#include "Actions/Status.h"
#include "Actions/Request.h"

namespace Actions {
  namespace ComponentList {
    ComponentHandle create();
    uint16_t getIndex(ComponentHandle handle);
    const Request* getRequest(uint16_t index);
    Status getStatus(uint16_t index);
    void updateRequest(uint16_t index, const Request *request);
    void updateStatus(uint16_t index, Status status);
  }
}

#endif
