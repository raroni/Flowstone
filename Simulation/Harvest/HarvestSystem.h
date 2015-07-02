#ifndef SIMULATION_HARVEST_SYSTEM_H
#define SIMULATION_HARVEST_SYSTEM_H

#include "Simulation/Harvest/HarvestResourceType.h"
#include "Simulation/Harvest/HarvestResourceHandle.h"

namespace Simulation {
  namespace HarvestSystem {
    HarvestResourceHandle createResource(HarvestResourceType type);
  }
}

#endif
