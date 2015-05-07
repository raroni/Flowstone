#ifndef SIMULATION_STEERING_H
#define SIMULATION_STEERING_H

#include "Physics/DynamicDriverHandle.h"
#include "Fixie/Vector3.h"

namespace Simulation {
  struct Steering {
    Fixie::Vector3 *target;
    Physics::DynamicDriverHandle dynamicDriverHandle;
  };
}

#endif
