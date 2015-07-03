#ifndef SIMULATION_TICKET_SYSTEM_H
#define SIMULATION_TICKET_SYSTEM_H

#include "Physics/BodyHandle.h"
#include "Database/EntityHandle.h"
#include "Simulation/Ticket/TicketRequestHandle.h"
#include "Simulation/Ticket/TicketTargetHandle.h"

namespace Simulation {
  namespace TicketSystem {
    TicketRequestHandle createRequest(Physics::BodyHandle handle);
    TicketTargetHandle createTarget(::Database::EntityHandle handle);
    void destroyTarget(TicketTargetHandle handle);
    void update();
  }
}

#endif
