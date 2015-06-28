#ifndef ACTIONS_INSTANCE_H
#define ACTIONS_INSTANCE_H

#include "Database/EntityHandle.h"
#include "Actions/InstanceHandle.h"
#include "Actions/Request.h"
#include "Actions/InstanceStatus.h"

namespace Actions {
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
