#ifndef SIMULATION_STEERING_SYSTEM_H
#define SIMULATION_STEERING_SYSTEM_H

#include "Simulation/Steering/Steering.h"
#include "Simulation/Steering/SteeringHandle.h"

namespace Simulation {
  namespace SteeringSystem {
    SteeringHandle create(Physics::ForceDriverHandle handle);
    void destroy(SteeringHandle handle);
    Steering get(SteeringHandle handle);
    void update();
  }
}

#endif
