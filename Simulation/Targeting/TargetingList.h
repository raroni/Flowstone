#ifndef SIMULATION_TARGETING_LIST_H
#define SIMULATION_TARGETING_LIST_H

#include "Fixie/Vector3.h"
#include "Database/EntityHandle.h"
#include "Simulation/Targeting/TargetingHandle.h"

namespace Simulation {
  namespace TargetingList {
    TargetingHandle create(::Database::EntityHandle entity);
    uint16_t getIndex(TargetingHandle handle);
    ::Database::EntityHandle getEntity(uint16_t index);
    void updatePosition(uint16_t index, const Fixie::Vector3 *position);
  }
}

#endif
