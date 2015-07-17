#ifndef SIMULATION_EVENT_TYPE_H
#define SIMULATION_EVENT_TYPE_H

#include <stdint.h>

namespace Simulation {
  enum class EventType : uint8_t {
    HarvestCompletion,
    HarvestWorkStart,
    SteeringStart,
    SteeringStop,

    Count
  };
}

#endif
