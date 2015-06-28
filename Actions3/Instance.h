#ifndef ACTIONS3_INSTANCE_H
#define ACTIONS3_INSTANCE_H

#include "Database/EntityHandle.h"
#include "Actions3/InstanceHandle.h"
#include "Actions3/Request.h"
#include "Actions3/InstanceStatus.h"

namespace Actions3 {
  namespace Instance {
    InstanceHandle create(Database::EntityHandle entity);
    const Request* getPendingRequest(InstanceHandle handle);
    const Request* getActiveRequest(InstanceHandle handle);
    InstanceStatus getStatus(InstanceHandle handle);
    Database::EntityHandle getEntityHandle(InstanceHandle handle);
    void startExecution(InstanceHandle handle);
    void scheduleRequest(InstanceHandle handle, const Request *request);
    void request(InstanceHandle handle, const Request *request);
    InstanceStatus getInstanceStatus(InstanceHandle handle);
    void cancel(InstanceHandle handle);
  }
}

#endif
