#ifndef SIMULATION_STEERING_EVENT_HANDLER_H
#define SIMULATION_STEERING_EVENT_HANDLER_H

#include "Simulation/Steering/SteeringEvent.h"

namespace Simulation {
  typedef void (*SteeringEventHandler)(const SteeringEvent *event);
}

#endif
