#include "Conrad/BitSet32.h"
#include "Simulation/Config.h"
#include "Simulation/Database/ComponentManager.h"

namespace Simulation {
  namespace ComponentManager {
    struct Set {
      ComponentHandle list[Config::componentMax];
    };

    Set sets[Config::entityMax];

    static_assert(32 >= Config::componentMax, "BitSet32 supports only 32 values.");
    BitSet32 existances[Config::entityMax];

    void link(EntityHandle entity, ComponentType type, ComponentHandle componentHandle) {
      uint8_t typeI = static_cast<uint8_t>(type);
      existances[entity].set(typeI);
      sets[entity].list[typeI] = componentHandle;
    }

    ComponentHandle get(EntityHandle entity, ComponentType type) {
      return sets[entity].list[static_cast<uint8_t>(type)];
    }

    bool has(EntityHandle entity, ComponentType type) {
      return existances[entity].get(static_cast<uint8_t>(type));
    }
  }
}
