#ifndef SIMULATION_DATABASE_H
#define SIMULATION_DATABASE_H

#include "Simulation/Database/EntityHandle.h"
#include "Simulation/Database/EntityList.h"
#include "Simulation/Database/ComponentType.h"
#include "Simulation/ResourceHandle.h"
#include "Simulation/ResourceType.h"
#include "Physics/DynamicBody.h"
#include "Physics/DynamicBodyIndex.h"

namespace Simulation {
  namespace Database {
    EntityList getEntityList();
    EntityHandle createEntity();
    bool hasComponent(EntityHandle entity, ComponentType type);
    Physics::DynamicBodyIndex createDynamicBody(EntityHandle entity);
    Physics::DynamicBodyIndex getDynamicBodyIndex(EntityHandle);
    Physics::DynamicBody getDynamicBody(EntityHandle entity);
    ResourceHandle createResource(EntityHandle entity, ResourceType type);
    void createMonster(EntityHandle entity);
  }
}

#endif
