#ifndef SIMULATION_DATABASE_H
#define SIMULATION_DATABASE_H

#include "Fixie/Vector2.h"
#include "Database/EntityHandle.h"
#include "Behavior/Handle.h"
#include "Behavior/BehaviorType.h"
#include "Actions/ComponentHandle.h"
#include "Physics/SphereColliderHandle.h"
#include "Physics/BodyHandle.h"
#include "Physics/DynamicDriverHandle.h"
#include "Physics/DynamicDriver.h"
#include "Physics/Body.h"
#include "Physics/ColliderType.h"
#include "Simulation/EntityList.h"
#include "Simulation/ComponentType.h"
#include "Simulation/ResourceHandle.h"
#include "Simulation/Steering/SteeringHandle.h"
#include "Simulation/Steering/Steering.h"
#include "Simulation/Targeting/TargetingHandle.h"
#include "Simulation/Drag/DragHandle.h"
#include "Simulation/ResourceType.h"
#include "Simulation/Pathfinding/PathfinderHandle.h"
#include "Simulation/Ticket/TicketRequestHandle.h"
#include "Simulation/Ticket/TicketTargetHandle.h"

namespace Simulation {
  namespace Database {
    EntityList getEntityList();
    ::Database::EntityHandle createEntity();
    bool hasComponent(::Database::EntityHandle entity, ComponentType type);
    Physics::BodyHandle createBody(::Database::EntityHandle entity);
    Physics::Body getBody(::Database::EntityHandle);
    Physics::BodyHandle getBodyHandle(::Database::EntityHandle);
    Physics::DynamicDriver getDynamicDriver(::Database::EntityHandle);
    Physics::DynamicDriverHandle getDynamicDriverHandle(::Database::EntityHandle);
    Physics::DynamicDriverHandle createDynamicDriver(::Database::EntityHandle);
    Physics::SphereColliderHandle createSphereCollider(::Database::EntityHandle entity, Fixie::Num radius, Physics::ColliderType type);
    ResourceHandle createResource(::Database::EntityHandle entity, ResourceType type);
    SteeringHandle createSteering(::Database::EntityHandle entityHandle);
    TargetingHandle createTargeting(::Database::EntityHandle ownerHandle, ::Database::EntityHandle targetHandle);
    PathfinderHandle createPathfinder(::Database::EntityHandle entityHandle, Fixie::Vector2 target);
    Behavior::Handle createBehavior(::Database::EntityHandle entity, Behavior::BehaviorType behaviorType);
    TicketRequestHandle createTicketRequest(::Database::EntityHandle entity);
    TicketTargetHandle createTicketTarget(::Database::EntityHandle entity);
    Actions::ComponentHandle createActions(::Database::EntityHandle entity);
    void destroySteering(::Database::EntityHandle entityHandle);
    void destroyPathfinder(::Database::EntityHandle entityHandle);
    Steering getSteering(::Database::EntityHandle entityHandle);
    SteeringHandle getSteeringHandle(::Database::EntityHandle entityHandle);
    TicketRequestHandle getTicketRequestHandle(::Database::EntityHandle entityHandle);
    DragHandle createDrag(::Database::EntityHandle entityHandle);
    void createMonster(::Database::EntityHandle entity);
  }
}

#endif
