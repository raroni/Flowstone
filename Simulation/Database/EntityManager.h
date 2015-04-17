#ifndef SIMULATION_ENTITY_MANAGER_H
#define SIMULATION_ENTITY_MANAGER_H

#include "Simulation/Config.h"
#include "Simulation/Database/EntityHandle.h"

namespace Simulation {
  namespace EntityManager {
    extern EntityHandle handles[Config::entityMax];
    EntityHandle create();
    uint16_t getCount();
  }
}

#endif
