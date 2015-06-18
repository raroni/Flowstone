#include "Database/EntityHandle.h"
#include "Database/EntityManager.h"
#include "Database/ComponentHandle.h"
#include "Database/ComponentManager.h"
#include "Behavior/System.h"
#include "Actions/System.h"
#include "Simulation/Config.h"
#include "Simulation/PhysicsHack.h"
#include "Simulation/Ticket/TicketSystem.h"
#include "Simulation/ResourceSystem.h"
#include "Simulation/Targeting/TargetingSystem.h"
#include "Simulation/Steering/SteeringSystem.h"
#include "Simulation/Pathfinding/PathfindingSystem.h"
#include "Simulation/Drag/DragSystem.h"
#include "Simulation/Database.h"

namespace Simulation {
  namespace Database {
    using namespace ::Database;
    EntityHandle entityHandles[Config::entityMax];
    EntityManager entityManager(entityHandles, Config::entityMax);

    ComponentHandle componentHandles[Config::entityMax*Config::componentMax];
    BitSet32 componentExistances[Config::entityMax];
    ComponentManager componentManager(componentHandles, componentExistances, Config::componentMax);

    EntityList getEntityList() {
      EntityList list;
      list.values = entityManager.handles;
      list.count = entityManager.getCount();
      return list;
    }

    EntityHandle createEntity() {
      return entityManager.create();
    }

    uint8_t convertTypeToInt(ComponentType type) {
      return static_cast<uint8_t>(type);
    }

    void linkComponent(EntityHandle entity, ComponentType type, ComponentHandle component) {
      componentManager.link(entity, convertTypeToInt(type), component);
    }

    void unlinkComponent(EntityHandle entity, ComponentType type) {
      componentManager.unlink(entity, convertTypeToInt(type));
    }

    ComponentHandle getComponent(EntityHandle entity, ComponentType type) {
      return componentManager.get(entity, convertTypeToInt(type));
    }

    bool hasComponent(EntityHandle entity, ComponentType type) {
      return componentManager.has(entity, convertTypeToInt(type));
    }

    Physics::DynamicDriverHandle createDynamicDriver(EntityHandle entity) {
      Physics::BodyHandle bodyHandle = getBodyHandle(entity);
      union {
        Physics::DynamicDriverHandle physicsHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.physicsHandle = physicsEngine.createDynamicDriver(bodyHandle);
      linkComponent(entity, ComponentType::DynamicDriver, caster.genericHandle);
      return caster.physicsHandle;
    }

    Physics::BodyHandle createBody(EntityHandle entity) {
      union {
        Physics::BodyHandle physicsHandle = physicsEngine.createBody();
        ComponentHandle genericHandle;
      } caster;

      linkComponent(entity, ComponentType::Body, caster.genericHandle);
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
      linkComponent(entity, ComponentType::SphereCollider, caster.genericHandle);
      return caster.physicsHandle;
    }

    Physics::BodyHandle getBodyHandle(EntityHandle entity) {
      union {
        Physics::BodyHandle physicsHandle;
        ComponentHandle genericHandle;
      } caster;

      caster.genericHandle = getComponent(entity, ComponentType::Body);
      return caster.physicsHandle;
    }

    ResourceHandle createResource(EntityHandle entity, ResourceType type) {
      union {
        ResourceHandle resourceHandle;
        ComponentHandle componentHandle;
      } caster;

      caster.resourceHandle = ResourceSystem::create(type);
      linkComponent(entity, ComponentType::Resource, caster.componentHandle);
      return caster.resourceHandle;
    }

    void createMonster(EntityHandle entity) {
      linkComponent(entity, ComponentType::Monster, ComponentHandle());
    }

    Physics::Body getBody(EntityHandle entity) {
      return physicsEngine.getBody(getBodyHandle(entity));
    }

    Physics::DynamicDriverHandle getDynamicDriverHandle(EntityHandle entityHandle) {
      union {
        Physics::DynamicDriverHandle physicsHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.genericHandle = getComponent(entityHandle, ComponentType::DynamicDriver);
      return caster.physicsHandle;
    }

    Physics::DynamicDriver getDynamicDriver(EntityHandle entity) {
      return physicsEngine.getDynamicDriver(getDynamicDriverHandle(entity));
    }

    SteeringHandle createSteering(EntityHandle entityHandle) {
      static_assert(sizeof(SteeringHandle) == sizeof(ComponentHandle), "Handle size must be the same.");
      union {
        SteeringHandle steeringHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.steeringHandle = SteeringSystem::create(getDynamicDriverHandle(entityHandle));
      linkComponent(entityHandle, ComponentType::Steering, caster.genericHandle);
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
      linkComponent(entityHandle, ComponentType::Pathfinder, caster.genericHandle);
      return caster.pathfinderHandle;
    }

    Actions::ComponentHandle getActionsHandle(EntityHandle entityHandle) {
      assert(hasComponent(entityHandle, ComponentType::Actions));
      static_assert(sizeof(PathfinderHandle) == sizeof(ComponentHandle), "Handle size must be the same.");
      union {
        Actions::ComponentHandle actionsHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.genericHandle = getComponent(entityHandle, ComponentType::Actions);
      return caster.actionsHandle;
    }

    Behavior::Handle createBehavior(EntityHandle entity, Behavior::BehaviorType behaviorType) {
      union {
        Behavior::Handle aiHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.aiHandle = Behavior::System::create(getActionsHandle(entity), behaviorType);
      linkComponent(entity, ComponentType::AI, caster.genericHandle);
      return caster.aiHandle;
    }

    TicketRequestHandle createTicketRequest(EntityHandle entity) {
      // todo: assert has physics body
      union {
        Behavior::Handle ticketHandle;
        ComponentHandle genericHandle;
      } caster;
      Physics::BodyHandle physicsBody = getBodyHandle(entity);
      caster.ticketHandle = TicketSystem::createSubscription(physicsBody);
      linkComponent(entity, ComponentType::TicketRequest, caster.genericHandle);
      return caster.ticketHandle;
    }

    Actions::ComponentHandle createActions(EntityHandle entity) {
      union {
        Behavior::Handle actionsHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.actionsHandle = Actions::System::createComponent(entity);
      linkComponent(entity, ComponentType::Actions, caster.genericHandle);
      return caster.actionsHandle;
    }

    PathfinderHandle getPathfinderHandle(EntityHandle entityHandle) {
      static_assert(sizeof(PathfinderHandle) == sizeof(ComponentHandle), "Handle size must be the same.");
      union {
        PathfinderHandle pathfinderHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.genericHandle = getComponent(entityHandle, ComponentType::Pathfinder);
      return caster.pathfinderHandle;
    }

    void destroyPathfinder(EntityHandle entityHandle) {
      PathfinderHandle pathfinderHandle = getPathfinderHandle(entityHandle);
      PathfindingSystem::destroy(pathfinderHandle);
      unlinkComponent(entityHandle, ComponentType::Pathfinder);
    }

    SteeringHandle getSteeringHandle(EntityHandle entityHandle) {
      static_assert(sizeof(SteeringHandle) == sizeof(ComponentHandle), "Handle size must be the same.");
      union {
        SteeringHandle steeringHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.genericHandle = getComponent(entityHandle, ComponentType::Steering);
      return caster.steeringHandle;
    }

    TicketRequestHandle getTicketRequestHandle(::Database::EntityHandle entityHandle) {
      static_assert(sizeof(SteeringHandle) == sizeof(ComponentHandle), "Handle size must be the same.");
      // todo has(ComponentType::TicketRequest)
      union {
        TicketRequestHandle requestHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.genericHandle = getComponent(entityHandle, ComponentType::TicketRequest);
      return caster.requestHandle;
    }

    Steering getSteering(EntityHandle entityHandle) {
      return SteeringSystem::get(getSteeringHandle(entityHandle));
    }

    void destroySteering(EntityHandle entityHandle) {
      SteeringHandle steeringHandle = getSteeringHandle(entityHandle);
      SteeringSystem::destroy(steeringHandle);
      unlinkComponent(entityHandle, ComponentType::Steering);
    }

    TargetingHandle createTargeting(EntityHandle ownerHandle, EntityHandle targetHandle) {
      // todo !has(Targeting)
      static_assert(sizeof(TargetingHandle) == sizeof(ComponentHandle), "Handle size must be the same.");
      union {
        TargetingHandle targetingHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.targetingHandle = TargetingSystem::create(targetHandle);
      linkComponent(ownerHandle, ComponentType::Targeting, caster.genericHandle);
      return caster.targetingHandle;
    }

    DragHandle createDrag(EntityHandle entityHandle) {
      static_assert(sizeof(DragHandle) == sizeof(ComponentHandle), "Handle size must be the same.");
      union {
        DragHandle dragHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.dragHandle = DragSystem::create(getDynamicDriverHandle(entityHandle));
      linkComponent(entityHandle, ComponentType::Drag, caster.genericHandle);
      return caster.dragHandle;
    }
  }
}
