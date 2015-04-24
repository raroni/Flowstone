#ifndef SIMULATION_STEERING_LIST_H
#define SIMULATION_STEERING_LIST_H

#include "Simulation/Config.h"
#include "Physics/ForceDriverHandle.h"
#include "Simulation/Steering/SteeringHandle.h"
#include "Simulation/Steering/Steering.h"

namespace Simulation {
  namespace SteeringList {
    extern Fixie::Vector3 targets[Config::steeringMax];
    extern Physics::ForceDriverHandle forceDriverHandles[Config::steeringMax];
    extern uint16_t count;

    SteeringHandle create(Physics::ForceDriverHandle handle);
    Steering get(SteeringHandle handle);
    void destroy(SteeringHandle handle);
  }
}

#endif
