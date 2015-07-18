#ifndef SIMULATION_STEERING_STOP_EVENT_H
#define SIMULATION_STEERING_STOP_EVENT_H

#include "Simulation/Event/EventType.h"
#include "Database/EntityHandle.h"

namespace Simulation {
  struct SteeringStopEvent {
    const EventType type = EventType::SteeringStop;
    Database::EntityHandle entity;
  };
}

#endif
