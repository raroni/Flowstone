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

    Physics::DynamicBodyIndex createDynamicBody(EntityHandle entity) {
      union {
        Physics::DynamicBodyIndex index = physicsEngine.createDynamicBody();
        ComponentHandle componentHandle;
      } caster;

      ComponentManager::link(entity, ComponentType::PhysicsDynamicBody, caster.componentHandle);
      return caster.index;
    }

    Physics::StaticSphereColliderHandle createStaticSphereCollider(EntityHandle entity, Fixie::Num radius) {
      Physics::StaticBodyIndex body = getStaticBodyIndex(entity);
      union {
        Physics::StaticSphereColliderHandle collider;
        ComponentHandle component;
      } caster;

      caster.collider = physicsEngine.createStaticSphereCollider(body, radius);
      ComponentManager::link(entity, ComponentType::PhysicsStaticSphereCollider, caster.component);
      return caster.collider;
    }

    Physics::DynamicSphereColliderHandle createDynamicSphereCollider(EntityHandle entity, Fixie::Num radius) {
      Physics::DynamicBodyIndex body = getDynamicBodyIndex(entity);
      union {
        Physics::DynamicSphereColliderHandle collider;
        ComponentHandle component;
      } caster;

      caster.collider = physicsEngine.createDynamicSphereCollider(body, radius);
      ComponentManager::link(entity, ComponentType::PhysicsDynamicSphereCollider, caster.component);
      return caster.collider;
    }

    Physics::StaticBodyIndex createStaticBody(EntityHandle entity) {
      union {
        Physics::StaticBodyIndex index = physicsEngine.createStaticBody();
        ComponentHandle componentHandle;
      } caster;

      ComponentManager::link(entity, ComponentType::PhysicsStaticBody, caster.componentHandle);
      return caster.index;
    }

    Physics::DynamicBodyIndex getDynamicBodyIndex(EntityHandle entity) {
      union {
        Physics::DynamicBodyIndex index;
        ComponentHandle componentHandle;
      } caster;

      caster.componentHandle = ComponentManager::get(entity, ComponentType::PhysicsDynamicBody);
      return caster.index;
    }

    Physics::StaticBodyIndex getStaticBodyIndex(EntityHandle entity) {
      union {
        Physics::StaticBodyIndex index;
        ComponentHandle componentHandle;
      } caster;

      caster.componentHandle = ComponentManager::get(entity, ComponentType::PhysicsStaticBody);
      return caster.index;
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

    Physics::DynamicBody getDynamicBody(EntityHandle entity) {
      union {
        Physics::DynamicBodyIndex index;
        ComponentHandle componentHandle;
      } caster;

      caster.componentHandle = ComponentManager::get(entity, ComponentType::PhysicsDynamicBody);
      return physicsEngine.getDynamicBody(caster.index);
    }

    Physics::StaticBody getStaticBody(EntityHandle entity) {
      union {
        Physics::StaticBodyIndex index;
        ComponentHandle componentHandle;
      } caster;

      caster.componentHandle = ComponentManager::get(entity, ComponentType::PhysicsStaticBody);
      return physicsEngine.getStaticBody(caster.index);
    }
  }
}
