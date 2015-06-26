#ifndef ACTIONS3_INSTANCE_H
#define ACTIONS3_INSTANCE_H

#include "Database/EntityHandle.h"
#include "Actions3/InstanceHandle.h"
#include "Actions3/ActionType.h"
#include "Actions3/InstanceStatus.h"

namespace Actions3 {
  namespace Instance {
    InstanceHandle create(Database::EntityHandle entity);
    ActionType getRequestActionType(InstanceHandle handle);
    InstanceStatus getStatus(InstanceHandle handle);
    Database::EntityHandle getEntityHandle(InstanceHandle handle);
    void startExecution(InstanceHandle handle);
    void scheduleRequest(InstanceHandle handle, ActionType actionType);
    void request(InstanceHandle handle, ActionType actionType);
    InstanceStatus getInstanceStatus(InstanceHandle handle);
    void cancel(InstanceHandle handle);
  }
}

#endif
