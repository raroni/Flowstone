#ifndef SIMULATION_TICKET_REQUEST_LIST_H
#define SIMULATION_TICKET_REQUEST_LIST_H

#include "Database/EntityHandle.h"
#include "Physics/BodyHandle.h"
#include "Simulation/Ticket/TicketRequestStatus.h"
#include "Simulation/Ticket/TicketRequestHandle.h"

namespace Simulation {
  namespace TicketRequestList {
    uint16_t getCount();
    uint16_t getIndex(TicketRequestHandle handle);
    TicketRequestHandle create(Physics::BodyHandle handle);
    TicketRequestStatus getStatus(uint16_t index);
    Database::EntityHandle getTarget(uint16_t index);
    void updateStatus(uint16_t index, TicketRequestStatus status);
    void updateTarget(uint16_t index, Database::EntityHandle handle);
  }
}

#endif
