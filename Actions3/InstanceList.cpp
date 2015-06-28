#include "Misc/HandleList.h"
#include "Actions3/ActionType.h"
#include "Actions3/InstanceList.h"

namespace Actions3 {
  namespace InstanceList {
    const static uint16_t max = 256;
    uint16_t indices[max];
    InstanceHandle handles[max];
    HandleList handleList(max, indices, handles);
    Request activeRequests[max];
    Request pendingRequests[max];
    Database::EntityHandle entityHandles[max];
    InstanceStatus statuses[max];

    InstanceHandle create(Database::EntityHandle entityHandle) {
      uint16_t index;
      InstanceHandle handle;
      handleList.create(&index, &handle);
      pendingRequests[index].type = ActionType::None;
      activeRequests[index].type = ActionType::None;
      entityHandles[index] = entityHandle;
      statuses[index] = InstanceStatus::Initialized;
      return handle;
    }

    Database::EntityHandle getEntityHandle(uint16_t index) {
      return entityHandles[index];
    }

    uint16_t getIndex(InstanceHandle handle) {
      return handleList.getIndex(handle);
    }

    const Request* getPendingRequest(uint16_t index) {
      return &pendingRequests[index];
    }

    const Request* getActiveRequest(uint16_t index) {
      return &activeRequests[index];
    }

    void updatePendingRequest(uint16_t index, const Request *request) {
      pendingRequests[index] = *request;
    }

    void updateActiveRequest(uint16_t index, const Request *request) {
      activeRequests[index] = *request;
    }

    InstanceStatus getStatus(uint16_t index) {
      return statuses[index];
    }
  }
}
