#ifndef SIMULATION_HARVEST_WORKER_LIST_H
#define SIMULATION_HARVEST_WORKER_LIST_H

#include "Simulation/Harvest/HarvestWorkerHandle.h"
#include "Simulation/Harvest/HarvestResourceHandle.h"

namespace Simulation {
  namespace HarvestWorkerList {
    HarvestWorkerHandle create(HarvestResourceHandle handle);
    HarvestResourceHandle getResourceHandle(uint16_t index);
    uint16_t getCount();
  }
}

#endif
