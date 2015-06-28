#include "Actions3/NewRequests.h"
#include "Actions3/PendingRequests.h"
#include "Actions3/Executions.h"
#include "Actions3/InstanceList.h"
#include "Actions3/Instance.h"

#include <assert.h>

namespace Actions3 {
  namespace Instance {
    namespace List = InstanceList;

    InstanceHandle create(Database::EntityHandle entity) {
      return List::create(entity);
    }

    Database::EntityHandle getEntityHandle(InstanceHandle handle) {
      uint16_t index = List::getIndex(handle);
      return List::getEntityHandle(index);
    }

    void startExecution(InstanceHandle handle) {
      Executions::start(handle);
      uint16_t index = List::getIndex(handle);
      List::updateActiveRequest(index, getPendingRequest(handle));
    }

    const Request* getPendingRequest(InstanceHandle handle) {
      uint16_t index = List::getIndex(handle);
      return List::getPendingRequest(index);
    }

    const Request* getActiveRequest(InstanceHandle handle) {
      uint16_t index = List::getIndex(handle);
      return List::getActiveRequest(index);
    }

    InstanceStatus getStatus(InstanceHandle handle) {
      uint16_t index = List::getIndex(handle);
      return List::getStatus(index);
    }

    void scheduleRequest(InstanceHandle handle, const Request *request) {
      NewRequests::set(handle, request);
    }

    void request(InstanceHandle handle, const Request *request) {
      uint16_t index = List::getIndex(handle);
      List::updatePendingRequest(index, request);
      PendingRequests::set(handle);
    }

    void cancel(InstanceHandle handle) {
      // todo
      assert(false);
    }
  }
}
