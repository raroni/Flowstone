#ifndef SIMULATION_TARGETING_LIST_H
#define SIMULATION_TARGETING_LIST_H

#include "Database/EntityHandle.h"
#include "Simulation/Targeting/TargetingHandle.h"

namespace Simulation {
  namespace TargetingList {
    TargetingHandle create(Database::EntityHandle targetEntity);
  }
}

#endif
