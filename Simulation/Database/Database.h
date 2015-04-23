#ifndef SIMULATION_DATABASE_H
#define SIMULATION_DATABASE_H

#include "Simulation/Database/EntityHandle.h"
#include "Simulation/Database/EntityList.h"
#include "Simulation/Database/ComponentType.h"
#include "Simulation/ResourceHandle.h"
#include "Simulation/ResourceType.h"
#include "Physics/SphereColliderHandle.h"
#include "Physics/BodyHandle.h"
#include "Physics/ForceDriverHandle.h"
#include "Physics/ForceDriver.h"
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
    Physics::ForceDriver getForceDriver(EntityHandle);
    ResourceHandle createResource(EntityHandle entity, ResourceType type);
    Physics::ForceDriverHandle createForceDriver(EntityHandle);
    Physics::SphereColliderHandle createSphereCollider(EntityHandle entity, Fixie::Num radius, Physics::ColliderType type);
    void createMonster(EntityHandle entity);
  }
}

#endif
