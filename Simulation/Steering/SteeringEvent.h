#ifndef SIMULATION_STEERING_EVENT_H
#define SIMULATION_STEERING_EVENT_H

#include "Database/EntityHandle.h"
#include "Simulation/Steering/SteeringEventType.h"

namespace Simulation {
  struct SteeringEvent {
    SteeringEventType type;
    ::Database::EntityHandle entity;
  };
}

#endif
