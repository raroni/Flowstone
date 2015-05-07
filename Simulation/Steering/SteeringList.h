#ifndef SIMULATION_STEERING_LIST_H
#define SIMULATION_STEERING_LIST_H

#include "Simulation/Config.h"
#include "Physics/DynamicDriverHandle.h"
#include "Simulation/Steering/SteeringHandle.h"
#include "Simulation/Steering/Steering.h"

namespace Simulation {
  namespace SteeringList {
    extern Fixie::Vector3 targets[Config::steeringMax];
    extern Physics::DynamicDriverHandle dynamicDriverHandles[Config::steeringMax];

    SteeringHandle create(Physics::DynamicDriverHandle handle);
    Steering get(SteeringHandle handle);
    uint16_t getCount();
    void destroy(SteeringHandle handle);
  }
}

#endif
