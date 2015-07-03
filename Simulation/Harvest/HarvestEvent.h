#ifndef SIMULATION_HARVEST_EVENT_H
#define SIMULATION_HARVEST_EVENT_H

#include "Database/EntityHandle.h"
#include "Simulation/Harvest/HarvestEventType.h"

namespace Simulation {
  struct HarvestEvent {
    HarvestEventType type;
    Database::EntityHandle worker;
    Database::EntityHandle resource;
  };
}

#endif
