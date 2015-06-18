#ifndef SIMULATION_TARGETING_SYSTEM_H
#define SIMULATION_TARGETING_SYSTEM_H

#include "Simulation/Targeting/TargetingHandle.h"
#include "Database/EntityHandle.h"

namespace Simulation {
  namespace TargetingSystem {
    TargetingHandle create(Database::EntityHandle targetEntity);
  }
}

#endif
