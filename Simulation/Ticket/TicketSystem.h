#ifndef SIMULATION_TICKET_SYSTEM_H
#define SIMULATION_TICKET_SYSTEM_H

#include "Simulation/Ticket/TicketSubscriptionHandle.h"

namespace Simulation {
  namespace TicketSystem {
    TicketSubscriptionHandle createSubscription(Physics::BodyHandle handle);
    void update();
  }
}

#endif
