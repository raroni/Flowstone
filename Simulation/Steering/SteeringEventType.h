#ifndef SIMULATION_STEERING_EVENT_TYPE_H
#define SIMULATION_STEERING_EVENT_TYPE_H

#include <stdint.h>

namespace Simulation {
  enum class SteeringEventType : uint8_t {
    Start,
    Stop
  };
}

#endif
