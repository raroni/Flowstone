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
        InstanceStatus status = Instance::getStatus(handle);
        if(
          status == InstanceStatus::Cancelled ||
          status == InstanceStatus::Initialized ||
          status == InstanceStatus::Completed
        ) {
          Instance::startExecution(handle);
          map.remove(i);
          i--;
        }
      }
    }
  }
}
