#ifndef SIMULATION_STEERING_START_EVENT_H
#define SIMULATION_STEERING_START_EVENT_H

#include "Simulation/Event/EventType.h"
#include "Database/EntityHandle.h"

namespace Simulation {
  struct SteeringStartEvent {
    const EventType type = EventType::SteeringStart;
    Database::EntityHandle entity;
  };
}

#endif
