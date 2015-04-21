#ifndef SIMULATION_DATABASE_H
#define SIMULATION_DATABASE_H

#include "Simulation/Database/EntityHandle.h"
#include "Simulation/Database/EntityList.h"
#include "Simulation/Database/ComponentType.h"
#include "Simulation/ResourceHandle.h"
#include "Simulation/ResourceType.h"
#include "Physics/StaticSphereColliderHandle.h"
#include "Physics/DynamicSphereColliderHandle.h"
#include "Physics/DynamicBody.h"
#include "Physics/DynamicBodyIndex.h"
#include "Physics/StaticBody.h"
#include "Physics/StaticBodyIndex.h"

namespace Simulation {
  namespace Database {
    EntityList getEntityList();
    EntityHandle createEntity();
    bool hasComponent(EntityHandle entity, ComponentType type);
    Physics::DynamicBodyIndex createDynamicBody(EntityHandle entity);
    Physics::StaticBodyIndex createStaticBody(EntityHandle entity);
    Physics::DynamicBodyIndex getDynamicBodyIndex(EntityHandle);
    Physics::StaticBodyIndex getStaticBodyIndex(EntityHandle);
    Physics::DynamicBody getDynamicBody(EntityHandle entity);
    Physics::StaticBody getStaticBody(EntityHandle entity);
    ResourceHandle createResource(EntityHandle entity, ResourceType type);
    Physics::StaticSphereColliderHandle createStaticSphereCollider(EntityHandle entity, Fixie::Num radius);
    Physics::DynamicSphereColliderHandle createDynamicSphereCollider(EntityHandle entity, Fixie::Num radius);
    void createMonster(EntityHandle entity);
  }
}

#endif
