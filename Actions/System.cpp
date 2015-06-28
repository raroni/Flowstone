#include "Actions/Executions.h"
#include "Actions/PendingRequests.h"
#include "Actions/NewRequests.h"
#include "Actions/ActionSetup.h"
#include "Actions/Instance.h"
#include "Actions/System.h"

namespace Actions {
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
