#include "Actions3/ActionTypeMap.h"
#include "Actions3/PendingRequests.h"

namespace Actions3 {
  namespace PendingRequests {
    ActionTypeMap map;

    void set(InstanceHandle handle, ActionType actionType) {
      map.set(handle, actionType);
    }

    void process() {

    }
  }
}
