#ifndef SIMULATION_COMPONENT_MANAGER_H
#define SIMULATION_COMPONENT_MANAGER_H

#include <stdint.h>
#include "Simulation/Database/EntityHandle.h"
#include "Simulation/Database/ComponentType.h"
#include "Simulation/Database/ComponentHandle.h"

namespace Simulation {
  namespace ComponentManager {
    extern const uint8_t max;

    void link(EntityHandle entity, ComponentType type, ComponentHandle componentHandle);
    void unlink(EntityHandle entity, ComponentType type);
    ComponentHandle get(EntityHandle entity, ComponentType type);
    bool has(EntityHandle entity, ComponentType);
  }
}

#endif
