#ifndef SIMULATION_ENTITY_LIST_H
#define SIMULATION_ENTITY_LIST_H

#include "Database/EntityHandle.h"

namespace Simulation {
  struct EntityList {
    Database::EntityHandle *values;
    uint16_t count = 0;
  };
}

#endif
