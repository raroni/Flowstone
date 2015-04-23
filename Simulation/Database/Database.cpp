#include "Simulation/PhysicsHack.h"
#include "Simulation/ResourceSystem.h"
#include "Simulation/Database/EntityManager.h"
#include "Simulation/Database/ComponentManager.h"
#include "Simulation/Database/Database.h"

namespace Simulation {
  namespace Database {
    EntityList getEntityList() {
      EntityList list;
      list.values = EntityManager::handles;
      list.count = EntityManager::getCount();
      return list;
    }

    EntityHandle createEntity() {
      return EntityManager::create();
    }

    bool hasComponent(EntityHandle entity, ComponentType type) {
      return ComponentManager::has(entity, type);
    }

    Physics::ForceDriverHandle createForceDriver(EntityHandle entity) {
      Physics::BodyHandle bodyHandle = getBodyHandle(entity);
      union {
        Physics::ForceDriverHandle physicsHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.physicsHandle = physicsEngine.createForceDriver(bodyHandle);
      ComponentManager::link(entity, ComponentType::ForceDriver, caster.genericHandle);
      return caster.physicsHandle;
    }

    Physics::BodyHandle createBody(EntityHandle entity) {
      union {
        Physics::BodyHandle physicsHandle = physicsEngine.createBody();
        ComponentHandle genericHandle;
      } caster;

      ComponentManager::link(entity, ComponentType::Body, caster.genericHandle);
      return caster.physicsHandle;
    }

    Physics::SphereColliderHandle createSphereCollider(EntityHandle entity, Fixie::Num radius, Physics::ColliderType type) {
      // todo: assert has body?
      Physics::BodyHandle body = getBodyHandle(entity);
      union {
        Physics::SphereColliderHandle physicsHandle;
        ComponentHandle genericHandle;
      } caster;

      caster.physicsHandle = physicsEngine.createSphereCollider(body, type, radius);
      ComponentManager::link(entity, ComponentType::SphereCollider, caster.genericHandle);
      return caster.physicsHandle;
    }

    Physics::BodyHandle getBodyHandle(EntityHandle entity) {
      union {
        Physics::BodyHandle physicsHandle;
        ComponentHandle genericHandle;
      } caster;

      caster.genericHandle = ComponentManager::get(entity, ComponentType::Body);
      return caster.physicsHandle;
    }

    ResourceHandle createResource(EntityHandle entity, ResourceType type) {
      union {
        ResourceHandle resourceHandle;
        ComponentHandle componentHandle;
      } caster;

      caster.resourceHandle = ResourceSystem::create(type);
      ComponentManager::link(entity, ComponentType::Resource, caster.componentHandle);
      return caster.resourceHandle;
    }

    void createMonster(EntityHandle entity) {
      ComponentManager::link(entity, ComponentType::Monster, ComponentHandle());
    }

    Physics::Body getBody(EntityHandle entity) {
      return physicsEngine.getBody(getBodyHandle(entity));
    }

    Physics::ForceDriver getForceDriver(EntityHandle entity) {
      union {
        Physics::ForceDriverHandle physicsHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.genericHandle = ComponentManager::get(entity, ComponentType::ForceDriver);
      return physicsEngine.getForceDriver(caster.physicsHandle);
    }
  }
}
