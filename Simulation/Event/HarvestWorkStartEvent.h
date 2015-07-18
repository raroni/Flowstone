#ifndef SIMULATION_HARVEST_WORK_START_EVENT_H
#define SIMULATION_HARVEST_WORK_START_EVENT_H

#include "Simulation/Event/EventType.h"
#include "Database/EntityHandle.h"

namespace Simulation {
  struct HarvestWorkStartEvent {
    const EventType type = EventType::HarvestWorkStart;
    Database::EntityHandle worker;
    Database::EntityHandle resource;
  };
}

#endif
