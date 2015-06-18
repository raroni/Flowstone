#ifndef SIMULATION_TICKET_TARGET_STATUS_H
#define SIMULATION_TICKET_TARGET_STATUS_H

#include <stdint.h>

namespace Simulation {
  enum class TicketTargetStatus : uint8_t {
    Free,
    Taken
  };
}

#endif
