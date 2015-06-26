#include "Actions3/NewRequests.h"
#include "Actions3/PendingRequests.h"
#include "Actions3/InstanceList.h"
#include "Actions3/Instance.h"

#include <assert.h>

namespace Actions3 {
  namespace Instance {
    namespace List = InstanceList;

    InstanceHandle create(Database::EntityHandle entity) {
      return List::create(entity);
    }

    ActionType getRequestActionType(InstanceHandle handle) {
      uint16_t index = List::getIndex(handle);
      return List::getRequestActionType(index);
    }

    InstanceStatus getStatus(InstanceHandle handle) {
      uint16_t index = List::getIndex(handle);
      return List::getStatus(index);
    }

    void scheduleRequest(InstanceHandle handle, ActionType actionType) {
      NewRequests::set(handle, actionType);
    }

    void request(InstanceHandle handle, ActionType actionType) {
      uint16_t index = List::getIndex(handle);
      List::updateRequestActionType(index, actionType);
      PendingRequests::set(handle, actionType);
    }

    void cancel(InstanceHandle handle) {
      // todo
      assert(false);
    }
  }
}
