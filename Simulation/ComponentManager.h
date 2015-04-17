#ifndef SIMULATION_COMPONENT_MANAGER_H
#define SIMULATION_COMPONENT_MANAGER_H

#include <stdint.h>
#include "Simulation/EntityHandle.h"
#include "Simulation/ComponentType.h"
#include "Simulation/ComponentHandle.h"

namespace Simulation {
  namespace ComponentManager {
    extern const uint8_t max;

    void link(EntityHandle entity, ComponentType type, ComponentHandle componentHandle);
    ComponentHandle get(EntityHandle entity, ComponentType type);
  }
}

#endif
