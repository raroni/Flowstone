#ifndef DATABASE_COMPONENT_MANAGER_H
#define DATABASE_COMPONENT_MANAGER_H

#include <stdint.h>
#include "Conrad/BitSet32.h"
#include "Database/EntityHandle.h"
#include "Database/ComponentHandle.h"

namespace Database {
  class ComponentManager {
  public:
    ComponentManager(ComponentHandle *handles, BitSet32 *existances, uint16_t componentMax);
    void link(EntityHandle entity, uint8_t type, ComponentHandle componentHandle);
    void unlink(EntityHandle entity, uint8_t type);
    ComponentHandle get(EntityHandle entity, uint8_t type);
    bool has(EntityHandle entity, uint8_t type);
  private:
    ComponentHandle *handles = nullptr;
    BitSet32 *existances = nullptr;
    uint16_t componentMax;
  };
}

#endif
