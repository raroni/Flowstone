#include "Actions3/Executions.h"
#include "Actions3/PendingRequests.h"
#include "Actions3/NewRequests.h"
#include "Actions3/ActionSetup.h"
#include "Actions3/Instance.h"
#include "Actions3/System.h"

namespace Actions3 {
  namespace System {
    void setup() {
      ActionSetup::execute();
    }

    InstanceHandle createInstance(Database::EntityHandle entity) {
      return Instance::create(entity);
    }

    void update() {
      Executions::process();
      //Cancellations::process();
      NewRequests::process();
      PendingRequests::process();
    }

    const Request* getPendingRequest(InstanceHandle handle) {
      return Instance::getPendingRequest(handle);
    }

    InstanceStatus getStatus(InstanceHandle handle) {
      return Instance::getStatus(handle);
    }

    void request(InstanceHandle handle, const Request *request) {
      Instance::scheduleRequest(handle, request);
    }
  }
}
