#include "Actions3/Instance.h"
#include "Actions3/RequestMap.h"
#include "Actions3/PendingRequests.h"

namespace Actions3 {
  namespace PendingRequests {
    RequestMap map;

    void set(InstanceHandle handle, const Request *request) {
      map.set(handle, request);
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
