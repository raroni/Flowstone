#ifndef SIMULATION_TICKET_SYSTEM_H
#define SIMULATION_TICKET_SYSTEM_H

#include "Physics/BodyHandle.h"
#include "Simulation/Ticket/TicketRequestHandle.h"

namespace Simulation {
  namespace TicketSystem {
    TicketRequestHandle createSubscription(Physics::BodyHandle handle);
    void update();
  }
}

#endif
