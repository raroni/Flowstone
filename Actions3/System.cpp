#include "Actions3/Executions.h"
#include "Actions3/PendingRequests.h"
#include "Actions3/NewRequests.h"
#include "Actions3/Instance.h"
#include "Actions3/System.h"

namespace Actions3 {
  namespace System {
    void setup() {
      // todo: configure actions
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

    ActionType getRequestActionType(InstanceHandle handle) {
      return Instance::getRequestActionType(handle);
    }

    InstanceStatus getStatus(InstanceHandle handle) {
      return Instance::getStatus(handle);
    }

    void request(InstanceHandle handle, ActionType actionType) {
      Instance::scheduleRequest(handle, actionType);
    }
  }
}
