#include <assert.h>
#include "Misc/HandleList.h"
#include "Actions/ActionTypes.h"
#include "Actions/ComponentList.h"

namespace Actions {
  namespace ComponentList {
    const uint16_t max = Config::componentMax;
    uint16_t indices[max];
    ComponentHandle handles[max];
    HandleList handleList(max, indices, handles);
    Status statuses[max];
    Request activeRequests[max];
    ActionStateHandle actionStateHandles[max];

    ComponentHandle create() {
      assert(handleList.getCount() != max);
      uint16_t index;
      ComponentHandle handle;
      handleList.create(&index, &handle);
      statuses[index] = Status::Completed;
      activeRequests[index].type = ActionTypes::empty;
      actionStateHandles[index] = 0;
      return handle;
    }

    uint16_t getIndex(ComponentHandle handle) {
      return handleList.getIndex(handle);
    }

    const Request* getActiveRequest(uint16_t index) {
      return &activeRequests[index];
    }

    void updateStatus(uint16_t index, Status status) {
      statuses[index] = status;
    }

    Status getStatus(uint16_t index) {
      return statuses[index];
    }

    void updateStateHandle(uint16_t componentIndex, ActionStateHandle stateHandle) {
      handles[componentIndex] = stateHandle;
    }

    void updateActiveRequest(uint16_t index, const Request *request) {
      activeRequests[index] = *request;
    }
  }
}
