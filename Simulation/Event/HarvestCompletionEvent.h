#ifndef SIMULATION_HARVEST_COMPLETION_EVENT_H
#define SIMULATION_HARVEST_COMPLETION_EVENT_H

#include "Simulation/Event/EventType.h"
#include "Database/EntityHandle.h"

namespace Simulation {
  struct HarvestCompletionEvent {
    const EventType type = EventType::HarvestCompletion;
    Database::EntityHandle resource;
  };
}

#endif
