#ifndef SIMULATION_HARVEST_RESOURCE_LIST_H
#define SIMULATION_HARVEST_RESOURCE_LIST_H

#include "Simulation/Harvest/HarvestResourceHandle.h"
#include "Simulation/Harvest/HarvestResourceType.h"

namespace Simulation {
  namespace HarvestResourceList {
    HarvestResourceHandle create(HarvestResourceType type);
    void destroy(HarvestResourceHandle handle);
  }
}

#endif
