#include "Simulation/Ticket/TicketRequestList.h"
#include "Simulation/Ticket/TicketRequestStatus.h"
#include "Simulation/Ticket/TicketSystem.h"

namespace Simulation {
  namespace TicketSystem {
    namespace RequestList = TicketRequestList;

    TicketRequestHandle createSubscription(Physics::BodyHandle handle) {
      return RequestList::create(handle);
    }

    void update() {
      uint16_t count = RequestList::getCount();
      for(uint16_t i=0; i<count; ++i) {
        TicketRequestStatus status = RequestList::getStatus(i);
        if(status == TicketRequestStatus::Waiting) {
          // set target
          RequestList::updateStatus(i, TicketRequestStatus::Completed);
        }
      }
    }
  }
}
