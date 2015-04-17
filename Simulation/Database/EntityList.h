#ifndef SIMULATION_ENTITY_LIST_H
#define SIMULATION_ENTITY_LIST_H

#include "Simulation/Database/EntityHandle.h"

namespace Simulation {
  struct EntityList {
    const EntityHandle *values;
    uint16_t count;
  };
}

#endif
