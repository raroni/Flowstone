#ifndef SIMULATION_HARVEST_WORKER_LIST_H
#define SIMULATION_HARVEST_WORKER_LIST_H

#include "Database/EntityHandle.h"
#include "Simulation/Harvest/HarvestWorkerHandle.h"
#include "Simulation/Harvest/HarvestResourceHandle.h"

namespace Simulation {
  namespace HarvestWorkerList {
    HarvestWorkerHandle create(Database::EntityHandle worker, Database::EntityHandle resource, HarvestResourceHandle resourceHandle);
    HarvestResourceHandle getResourceHandle(uint16_t index);
    uint16_t getCount();
  }
}

#endif
