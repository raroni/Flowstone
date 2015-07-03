#ifndef SIMULATION_HARVEST_EVENT_LIST_H
#define SIMULATION_HARVEST_EVENT_LIST_H

#include <stdint.h>
#include "Simulation/Harvest/HarvestEvent.h"

namespace Simulation {
  namespace HarvestEventList {
    uint16_t getCount();
    void clear();
    const HarvestEvent* get(uint16_t index);
  }
}

#endif
