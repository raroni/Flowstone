#ifndef SIMULATION_PATHFINDING_SYSTEM_H
#define SIMULATION_PATHFINDING_SYSTEM_H

#include "Fixie/Vector2.h"
#include "Physics/BodyHandle.h"
#include "Simulation/Steering/SteeringHandle.h"
#include "Simulation/Pathfinding/PathfinderHandle.h"

namespace Simulation {
  namespace PathfindingSystem {
    PathfinderHandle create(Physics::BodyHandle bodyHandle, SteeringHandle handle, Fixie::Vector2 target);
    void destroy(PathfinderHandle handle);
    void update();
  }
}

#endif
