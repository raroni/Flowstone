#include "Simulation/Ticket/TicketSubscriptionList.h"
#include "Simulation/Ticket/TicketSystem.h"

namespace Simulation {
  namespace TicketSystem {
    TicketSubscriptionHandle createSubscription(Physics::BodyHandle handle) {
      TicketSubscriptionList::create(handle);
    }

    void update() {

    }
  }
}
