#ifndef SIMULATION_TICKET_REQUEST_LIST_H
#define SIMULATION_TICKET_REQUEST_LIST_H

#include "Physics/BodyHandle.h"
#include "Simulation/Ticket/TicketRequestStatus.h"
#include "Simulation/Ticket/TicketRequestHandle.h"

namespace Simulation {
  namespace TicketRequestList {
    uint16_t getCount();
    uint16_t getIndex(TicketRequestHandle handle);
    TicketRequestHandle create(Physics::BodyHandle handle);
    TicketRequestStatus getStatus(uint16_t index);
    void updateStatus(uint16_t index, TicketRequestStatus status);
  }
}

#endif
