#include "Simulation/PhysicsHack.h"
#include "Simulation/EntityManager.h"
#include "Simulation/ComponentManager.h"
#include "Simulation/Database.h"

namespace Simulation {
  namespace Database {
    EntityHandle createEntity() {
      return EntityManager::create();
    }

    Physics::DynamicBodyIndex createDynamicBody(EntityHandle entity) {
      union {
        Physics::DynamicBodyIndex index = physicsEngine.createDynamicBody();
        ComponentHandle componentHandle;
      } caster;

      ComponentManager::link(entity, ComponentType::PhysicsDynamicBody, caster.componentHandle);
      return caster.index;
    }

    Physics::DynamicBody getDynamicBody(EntityHandle entity) {
      union {
        Physics::DynamicBodyIndex index;
        ComponentHandle componentHandle;
      } caster;

      caster.componentHandle = ComponentManager::get(entity, ComponentType::PhysicsDynamicBody);
      return physicsEngine.getDynamicBody(caster.index);
    }
  }
}
