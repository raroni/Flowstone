#include "Database/EntityHandle.h"
#include "Database/EntityManager.h"
#include "Database/ComponentHandle.h"
#include "Database/ComponentManager.h"
#include "Behavior/System.h"
#include "Actions/System.h"
#include "Simulation/Config.h"
#include "Simulation/PhysicsHack.h"
#include "Simulation/Ticket/TicketSystem.h"
#include "Simulation/Harvest/HarvestSystem.h"
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

    HarvestResourceHandle createHarvestResource(EntityHandle entity, HarvestResourceType type) {
      union {
        HarvestResourceHandle resourceHandle;
        ComponentHandle componentHandle;
      } caster;

      caster.resourceHandle = HarvestSystem::createResource(type);
      linkComponent(entity, ComponentType::HarvestResource, caster.componentHandle);
      return caster.resourceHandle;
    }

    HarvestResourceHandle getHarvestResourceHandle(::Database::EntityHandle entityHandle) {
      assert(hasComponent(entityHandle, ComponentType::HarvestResource));
      static_assert(sizeof(HarvestResourceHandle) == sizeof(ComponentHandle), "Handle size must be the same.");
      union {
        HarvestResourceHandle resourceHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.genericHandle = getComponent(entityHandle, ComponentType::HarvestResource);
      return caster.resourceHandle;
    }

    HarvestWorkerHandle createHarvestWorker(::Database::EntityHandle worker, ::Database::EntityHandle resource) {
      union {
        HarvestWorkerHandle workerHandle;
        ComponentHandle componentHandle;
      } caster;
      HarvestResourceHandle resourceHandle = getHarvestResourceHandle(resource);
      caster.workerHandle = HarvestSystem::createWorker(worker, resource, resourceHandle);
      linkComponent(worker, ComponentType::HarvestWorker, caster.componentHandle);
      return caster.workerHandle;
    }

    void createWorker(EntityHandle entity) {
      linkComponent(entity, ComponentType::Worker, ComponentHandle());
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
      Physics::DynamicDriverHandle physicsDriverHandle = getDynamicDriverHandle(entityHandle);
      caster.steeringHandle = SteeringSystem::create(entityHandle, physicsDriverHandle);
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

    Actions::InstanceHandle getActionsHandle(EntityHandle entityHandle) {
      assert(hasComponent(entityHandle, ComponentType::Actions));
      static_assert(sizeof(PathfinderHandle) == sizeof(ComponentHandle), "Handle size must be the same.");
      union {
        Actions::InstanceHandle actionsHandle;
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
        TicketRequestHandle ticketHandle;
        ComponentHandle genericHandle;
      } caster;
      Physics::BodyHandle physicsBody = getBodyHandle(entity);
      caster.ticketHandle = TicketSystem::createRequest(physicsBody);
      linkComponent(entity, ComponentType::TicketRequest, caster.genericHandle);
      return caster.ticketHandle;
    }

    TicketTargetHandle createTicketTarget(EntityHandle entity) {
      // todo: assert has physics body
      union {
        TicketTargetHandle ticketHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.ticketHandle = TicketSystem::createTarget(entity);
      linkComponent(entity, ComponentType::TicketTarget, caster.genericHandle);
      return caster.ticketHandle;
    }

    Actions::InstanceHandle createActions(EntityHandle entity) {
      union {
        Behavior::Handle actionsHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.actionsHandle = Actions::System::createInstance(entity);
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

    TicketTargetHandle getTicketTargetHandle(::Database::EntityHandle entityHandle) {
      assert(hasComponent(entityHandle, ComponentType::TicketTarget));
      static_assert(sizeof(TicketTargetHandle) == sizeof(ComponentHandle), "Handle size must be the same.");
      union {
        HarvestResourceHandle ticketHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.genericHandle = getComponent(entityHandle, ComponentType::TicketTarget);
      return caster.ticketHandle;
    }

    void destroyHarvestResource(EntityHandle entityHandle) {
      assert(hasComponent(entityHandle, ComponentType::HarvestResource));
      HarvestResourceHandle resourceHandle = getHarvestResourceHandle(entityHandle);
      HarvestSystem::destroyResource(resourceHandle);
      unlinkComponent(entityHandle, ComponentType::HarvestResource);
    }

    void destroyTicketTarget(EntityHandle entityHandle) {
      assert(hasComponent(entityHandle, ComponentType::TicketTarget));
      TicketTargetHandle ticketHandle = getTicketTargetHandle(entityHandle);
      TicketSystem::destroyTarget(ticketHandle);
      unlinkComponent(entityHandle, ComponentType::TicketTarget);
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
