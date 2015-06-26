#include "Misc/HandleList.h"
#include "Actions3/ActionType.h"
#include "Actions3/InstanceList.h"

namespace Actions3 {
  namespace InstanceList {
    const static uint16_t max = 256;
    uint16_t indices[max];
    InstanceHandle handles[max];
    HandleList handleList(max, indices, handles);
    ActionType activeActionTypes[max];
    ActionType requestActionTypes[max];
    Database::EntityHandle entityHandles[max];
    InstanceStatus statuses[max];

    InstanceHandle create(Database::EntityHandle entityHandle) {
      uint16_t index;
      InstanceHandle handle;
      handleList.create(&index, &handle);
      requestActionTypes[index] = ActionType::None;
      activeActionTypes[index] = ActionType::None;
      entityHandles[index] = entityHandle;
      statuses[index] = InstanceStatus::Initialized;
      return handle;
    }

    uint16_t getIndex(InstanceHandle handle) {
      return handleList.getIndex(handle);
    }

    ActionType getRequestActionType(uint16_t index) {
      return requestActionTypes[index];
    }

    void updateRequestActionType(uint16_t index, ActionType type) {
      requestActionTypes[index] = type;
    }

    InstanceStatus getStatus(uint16_t index) {
      return statuses[index];
    }
  }
}
