#include "Actions3/Instance.h"
#include "Actions3/InstanceHandleSet.h"
#include "Actions3/PendingRequests.h"

namespace Actions3 {
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
