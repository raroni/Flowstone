#include <assert.h>
#include "Actions3/ActionTypeMap.h"
#include "Actions3/Instance.h"
#include "Actions3/NewRequests.h"

namespace Actions3 {
  namespace NewRequests {
    ActionTypeMap map;

    void set(InstanceHandle handle, ActionType type) {
      map.set(handle, type);
    }

    void process() {
      for(uint16_t i=0; i<map.getCount(); ++i) {
        InstanceHandle instanceHandle = map.getHandle(i);
        ActionType actionType = map.getActionType(i);
        Instance::request(instanceHandle, actionType);

        InstanceStatus status = Instance::getStatus(instanceHandle);
        if(status == InstanceStatus::Executing) {
          Instance::cancel(instanceHandle);
        }
      }
      map.clear();
    }
  }
}
