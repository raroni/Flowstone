#ifndef SIMULATION_DATABASE_H
#define SIMULATION_DATABASE_H

#include "Simulation/EntityHandle.h"
#include "Physics/DynamicBody.h"
#include "Physics/DynamicBodyIndex.h"

namespace Simulation {
  namespace Database {
    EntityHandle createEntity();
    Physics::DynamicBodyIndex createDynamicBody(EntityHandle entity);
    Physics::DynamicBody getDynamicBody(EntityHandle entity);
  }
}

#endif
