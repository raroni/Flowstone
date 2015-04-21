#ifndef SIMULATION_RESOURCE_MANAGER_H
#define SIMULATION_RESOURCE_MANAGER_H

#include "Simulation/ResourceType.h"
#include "Simulation/ResourceHandle.h"

namespace Simulation {
  namespace ResourceSystem {
    ResourceHandle create(ResourceType type);
  }
}

#endif
