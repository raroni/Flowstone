#ifndef SIMULATION_TICKET_REQUEST_STATUS_H
#define SIMULATION_TICKET_REQUEST_STATUS_H

#include <stdint.h>

namespace Simulation {
  enum class TicketRequestStatus : uint8_t {
    Waiting,
    Completed
  };
}

#endif
