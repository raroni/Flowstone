#ifndef ACTIONS_INSTANCE_LIST_H
#define ACTIONS_INSTANCE_LIST_H

#include "Database/EntityHandle.h"
#include "Actions/InstanceHandle.h"
#include "Actions/InstanceList.h"
#include "Actions/Request.h"
#include "Actions/InstanceStatus.h"

namespace Actions {
  namespace InstanceList {
    InstanceHandle create(Database::EntityHandle entity);
    uint16_t getIndex(InstanceHandle handle);
    const Request* getPendingRequest(uint16_t index);
    const Request* getActiveRequest(uint16_t index);
    void updatePendingRequest(uint16_t index, const Request *request);
    void updateActiveRequest(uint16_t index, const Request *request);
    Database::EntityHandle getEntityHandle(uint16_t index);
    InstanceStatus getStatus(uint16_t index);
  }
}

#endif
