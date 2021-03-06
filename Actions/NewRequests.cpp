#include <assert.h>
#include "Actions/RequestMap.h"
#include "Actions/Instance.h"
#include "Actions/NewRequests.h"

namespace Actions {
  namespace NewRequests {
    RequestMap map;

    void set(InstanceHandle handle, const Request *request) {
      map.set(handle, request);
    }

    void process() {
      for(uint16_t i=0; i<map.getCount(); ++i) {
        InstanceHandle instanceHandle = map.getHandle(i);
        const Request *request = map.getRequest(i);
        Instance::request(instanceHandle, request);

        InstanceStatus status = Instance::getStatus(instanceHandle);
        if(status == InstanceStatus::Executing) {
          Instance::cancel(instanceHandle);
        }
      }
      map.clear();
    }
  }
}
