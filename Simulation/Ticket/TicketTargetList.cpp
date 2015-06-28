#include "Misc/HandleList.h"
#include "Simulation/Ticket/TicketTargetList.h"

namespace Simulation {
  namespace TicketTargetList {
    static const uint16_t max = 32;
    uint16_t indices[max];
    uint16_t handles[max];
    Database::EntityHandle entityHandles[max];
    TicketTargetStatus statuses[max];
    HandleList handleList(max, indices, handles);

    uint16_t getCount() {
      return handleList.getCount();
    }

    TicketTargetHandle create(Database::EntityHandle entityHandle) {
      uint16_t index;
      TicketTargetHandle targetHandle;
      handleList.create(&index, &targetHandle);
      entityHandles[index] = entityHandle;
      statuses[index] = TicketTargetStatus::Free;
      return targetHandle;
    }

    TicketTargetStatus getStatus(uint16_t index) {
      return statuses[index];
    }

    Database::EntityHandle getEntityHandle(uint16_t index) {
      return entityHandles[index];
    }

    void updateStatus(uint16_t index, TicketTargetStatus status) {
      statuses[index] = status;
    }
  }
}
