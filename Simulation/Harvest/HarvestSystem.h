#ifndef SIMULATION_HARVEST_SYSTEM_H
#define SIMULATION_HARVEST_SYSTEM_H

#include "Simulation/Harvest/HarvestResourceType.h"
#include "Simulation/Harvest/HarvestResourceHandle.h"
#include "Simulation/Harvest/HarvestWorkerHandle.h"

namespace Simulation {
  namespace HarvestSystem {
    HarvestResourceHandle createResource(HarvestResourceType type);
    void destroyResource(HarvestResourceHandle resource);
    HarvestWorkerHandle createWorker(HarvestResourceHandle resource);
  }
}

#endif
