#ifndef SIMULATION_DATABASE_H
#define SIMULATION_DATABASE_H

#include "Simulation/Database/EntityHandle.h"
#include "Simulation/Database/EntityList.h"
#include "Simulation/Database/ComponentType.h"
#include "Physics/DynamicBody.h"
#include "Physics/DynamicBodyIndex.h"

namespace Simulation {
  namespace Database {
    EntityList getEntityList();
    EntityHandle createEntity();
    bool hasComponent(EntityHandle entity, ComponentType type);
    Physics::DynamicBodyIndex createDynamicBody(EntityHandle entity);
    Physics::DynamicBody getDynamicBody(EntityHandle entity);
  }
}

#endif
