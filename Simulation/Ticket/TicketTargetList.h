#ifndef SIMULATION_TICKET_TARGET_LIST_H
#define SIMULATION_TICKET_TARGET_LIST_H

#include "Database/EntityHandle.h"
#include "Simulation/Ticket/TicketTargetStatus.h"
#include "Simulation/Ticket/TicketTargetHandle.h"

namespace Simulation {
  namespace TicketTargetList {
    uint16_t getCount();
    TicketTargetHandle create(Database::EntityHandle handle);
    TicketTargetStatus getStatus(uint16_t index);
    Database::EntityHandle getEntityHandle(uint16_t index);
    void updateStatus(uint16_t index, TicketTargetStatus status);
  }
}

#endif
