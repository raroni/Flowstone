#ifndef ACTIONS3_INSTANCE_LIST_H
#define ACTIONS3_INSTANCE_LIST_H

#include "Database/EntityHandle.h"
#include "Actions3/InstanceHandle.h"
#include "Actions3/InstanceList.h"
#include "Actions3/Request.h"
#include "Actions3/InstanceStatus.h"

namespace Actions3 {
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
