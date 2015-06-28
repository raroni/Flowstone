#include "Actions/Instance.h"
#include "Actions/InstanceHandleSet.h"
#include "Actions/PendingRequests.h"

namespace Actions {
  namespace PendingRequests {
    InstanceHandleSet handleSet;

    void set(InstanceHandle handle) {
      handleSet.insert(handle);
    }

    void process() {
      for(uint16_t i=0; i<handleSet.getCount(); ++i) {
        InstanceHandle handle = handleSet.getHandle(i);
        InstanceStatus status = Instance::getStatus(handle);
        if(
          status == InstanceStatus::Cancelled ||
          status == InstanceStatus::Initialized ||
          status == InstanceStatus::Completed
        ) {
          Instance::startExecution(handle);
          handleSet.remove(i);
          i--;
        }
      }
    }
  }
}
