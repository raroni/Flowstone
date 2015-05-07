#ifndef SIMULATION_DATABASE_H
#define SIMULATION_DATABASE_H

#include "Fixie/Vector2.h"
#include "Simulation/Database/EntityHandle.h"
#include "Simulation/Database/EntityList.h"
#include "Simulation/Database/ComponentType.h"
#include "Simulation/ResourceHandle.h"
#include "Simulation/Steering/SteeringHandle.h"
#include "Simulation/Steering/Steering.h"
#include "Simulation/Drag/DragHandle.h"
#include "Simulation/ResourceType.h"
#include "Simulation/Pathfinding/PathfinderHandle.h"
#include "Physics/SphereColliderHandle.h"
#include "Physics/BodyHandle.h"
#include "Physics/DynamicDriverHandle.h"
#include "Physics/DynamicDriver.h"
#include "Physics/Body.h"
#include "Physics/ColliderType.h"

namespace Simulation {
  namespace Database {
    EntityList getEntityList();
    EntityHandle createEntity();
    bool hasComponent(EntityHandle entity, ComponentType type);
    Physics::BodyHandle createBody(EntityHandle entity);
    Physics::Body getBody(EntityHandle);
    Physics::BodyHandle getBodyHandle(EntityHandle);
    Physics::DynamicDriver getDynamicDriver(EntityHandle);
    Physics::DynamicDriverHandle getDynamicDriverHandle(EntityHandle);
    Physics::DynamicDriverHandle createDynamicDriver(EntityHandle);
    Physics::SphereColliderHandle createSphereCollider(EntityHandle entity, Fixie::Num radius, Physics::ColliderType type);
    ResourceHandle createResource(EntityHandle entity, ResourceType type);
    SteeringHandle createSteering(EntityHandle entityHandle);
    PathfinderHandle createPathfinder(EntityHandle entityHandle, Fixie::Vector2 target);
    void destroySteering(EntityHandle entityHandle);
    void destroyPathfinder(EntityHandle entityHandle);
    Steering getSteering(EntityHandle entityHandle);
    SteeringHandle getSteeringHandle(EntityHandle entityHandle);
    DragHandle createDrag(EntityHandle entityHandle);
    void createMonster(EntityHandle entity);
  }
}

#endif
