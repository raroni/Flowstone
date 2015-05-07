#include "Simulation/PhysicsHack.h"
#include "Simulation/ResourceSystem.h"
#include "Simulation/Steering/SteeringSystem.h"
#include "Simulation/Pathfinding/PathfindingSystem.h"
#include "Simulation/Drag/DragSystem.h"
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

    Physics::ForceDriverHandle getForceDriverHandle(EntityHandle entityHandle) {
      union {
        Physics::ForceDriverHandle physicsHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.genericHandle = ComponentManager::get(entityHandle, ComponentType::ForceDriver);
      return caster.physicsHandle;
    }

    Physics::ForceDriver getForceDriver(EntityHandle entity) {
      return physicsEngine.getForceDriver(getForceDriverHandle(entity));
    }

    SteeringHandle createSteering(EntityHandle entityHandle) {
      static_assert(sizeof(SteeringHandle) == sizeof(ComponentHandle), "Handle size must be the same.");
      union {
        SteeringHandle steeringHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.steeringHandle = SteeringSystem::create(getForceDriverHandle(entityHandle));
      ComponentManager::link(entityHandle, ComponentType::Steering, caster.genericHandle);
      return caster.steeringHandle;
    }

    PathfinderHandle createPathfinder(EntityHandle entityHandle, Fixie::Vector2 target) {
      static_assert(sizeof(PathfinderHandle) == sizeof(ComponentHandle), "Handle size must be the same.");
      assert(hasComponent(entityHandle, ComponentType::Steering));
      SteeringHandle steeringHandle = getSteeringHandle(entityHandle);
      Physics::BodyHandle bodyHandle = getBodyHandle(entityHandle);
      union {
        PathfinderHandle pathfinderHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.pathfinderHandle = PathfindingSystem::create(bodyHandle, steeringHandle, target);
      ComponentManager::link(entityHandle, ComponentType::Pathfinder, caster.genericHandle);
      return caster.pathfinderHandle;
    }

    PathfinderHandle getPathfinderHandle(EntityHandle entityHandle) {
      static_assert(sizeof(PathfinderHandle) == sizeof(ComponentHandle), "Handle size must be the same.");
      union {
        PathfinderHandle pathfinderHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.genericHandle = ComponentManager::get(entityHandle, ComponentType::Pathfinder);
      return caster.pathfinderHandle;
    }

    void destroyPathfinder(EntityHandle entityHandle) {
      PathfinderHandle pathfinderHandle = getPathfinderHandle(entityHandle);
      PathfindingSystem::destroy(pathfinderHandle);
      ComponentManager::unlink(entityHandle, ComponentType::Pathfinder);
    }

    SteeringHandle getSteeringHandle(EntityHandle entityHandle) {
      static_assert(sizeof(SteeringHandle) == sizeof(ComponentHandle), "Handle size must be the same.");
      union {
        SteeringHandle steeringHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.genericHandle = ComponentManager::get(entityHandle, ComponentType::Steering);
      return caster.steeringHandle;
    }

    Steering getSteering(EntityHandle entityHandle) {
      return SteeringSystem::get(getSteeringHandle(entityHandle));
    }

    void destroySteering(EntityHandle entityHandle) {
      SteeringHandle steeringHandle = getSteeringHandle(entityHandle);
      SteeringSystem::destroy(steeringHandle);
      ComponentManager::unlink(entityHandle, ComponentType::Steering);
    }

    DragHandle createDrag(EntityHandle entityHandle) {
      static_assert(sizeof(DragHandle) == sizeof(ComponentHandle), "Handle size must be the same.");
      union {
        DragHandle dragHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.dragHandle = DragSystem::create(getForceDriverHandle(entityHandle));
      ComponentManager::link(entityHandle, ComponentType::Drag, caster.genericHandle);
      return caster.dragHandle;
    }
  }
}
