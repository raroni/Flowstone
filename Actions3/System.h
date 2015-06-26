#ifndef ACTIONS3_SYSTEM_H
#define ACTIONS3_SYSTEM_H

#include "Database/EntityHandle.h"
#include "Actions3/InstanceHandle.h"
#include "Actions3/ActionType.h"
#include "Actions3/InstanceStatus.h"

namespace Actions3 {
  namespace System {
    void setup();
    InstanceHandle createInstance(Database::EntityHandle entity);
    void update();
    ActionType getRequestActionType(InstanceHandle handle);
    InstanceStatus getStatus(InstanceHandle handle);
    void request(InstanceHandle handle, ActionType actionType);
  }
}

#endif
