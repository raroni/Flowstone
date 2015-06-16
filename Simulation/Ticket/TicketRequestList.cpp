#include "Misc/HandleList.h"
#include "Simulation/Ticket/TicketRequestList.h"

namespace Simulation {
  namespace TicketRequestList {
    static const uint16_t max = 32;
    uint16_t indices[max];
    uint16_t handles[max];
    TicketRequestStatus statuses[max];
    HandleList handleList(max, indices, handles);

    TicketRequestHandle create(Physics::BodyHandle physicsBodyHandle) {
      uint16_t index;
      TicketRequestHandle ticketRequestHandle;
      handleList.create(&index, &ticketRequestHandle);
      statuses[index] = TicketRequestStatus::Waiting;
      return ticketRequestHandle;
    }

    uint16_t getIndex(TicketRequestHandle handle) {
      return handleList.getIndex(handle);
    }

    TicketRequestStatus getStatus(uint16_t index) {
      return statuses[index];
    }

    void updateStatus(uint16_t index, TicketRequestStatus status) {
      statuses[index] = status;
    }

    uint16_t getCount() {
      return handleList.getCount();
    }
  }
}
