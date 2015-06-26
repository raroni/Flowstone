#ifndef ACTIONS3_INSTANCE_LIST_H
#define ACTIONS3_INSTANCE_LIST_H

#include "Database/EntityHandle.h"
#include "Actions3/InstanceHandle.h"
#include "Actions3/InstanceList.h"
#include "Actions3/ActionType.h"
#include "Actions3/InstanceStatus.h"

namespace Actions3 {
  namespace InstanceList {
    InstanceHandle create(Database::EntityHandle entity);
    uint16_t getIndex(InstanceHandle handle);
    ActionType getRequestActionType(uint16_t index);
    void updateRequestActionType(uint16_t index, ActionType type);
    InstanceStatus getStatus(uint16_t index);
  }
}

#endif
