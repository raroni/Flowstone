#include "Actions3/Instance.h"
#include "Actions3/ActionTypeMap.h"
#include "Actions3/PendingRequests.h"

namespace Actions3 {
  namespace PendingRequests {
    ActionTypeMap map;

    void set(InstanceHandle handle, ActionType actionType) {
      map.set(handle, actionType);
    }

    void process() {
      for(uint16_t i=0; i<map.getCount(); ++i) {
        InstanceHandle handle = map.getHandle(i);
        if(
          Instance::getStatus(handle) == InstanceStatus::Cancelled ||
          Instance::getStatus(handle) == InstanceStatus::Initialized ||
          Instance::getStatus(handle) == InstanceStatus::Completed
        ) {
          ActionType type = map.getActionType(i);
          Instance::startExecution(type);
          map.remove(i);
          i--;
        }
      }
    }
  }
}
