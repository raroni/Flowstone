#include <assert.h>
#include "Database/ComponentManager.h"

namespace Database {
  ComponentManager::ComponentManager(ComponentHandle *handles, BitSet32 *existances, uint16_t componentMax) :
  handles(handles),
  existances(existances),
  componentMax(componentMax) {
    assert(componentMax <= 32);
  }

  void ComponentManager::link(EntityHandle entityHandle, uint8_t type, ComponentHandle componentHandle) {
    assert(type < componentMax);
    existances[entityHandle].set(type);
    handles[entityHandle*componentMax+type] = componentHandle;
  }

  void ComponentManager::unlink(EntityHandle entity, uint8_t type) {
    assert(type < componentMax);
    existances[entity].unset(type);
  }

  ComponentHandle ComponentManager::get(EntityHandle entity, uint8_t type) {
    return handles[entity*componentMax+type];
  }

  bool ComponentManager::has(EntityHandle entity, uint8_t type) {
    return existances[entity].get(type);
  }
}
