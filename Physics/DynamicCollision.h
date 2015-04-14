#ifndef PHYSICS_DYNAMIC_COLLISION_H
#define PHYSICS_DYNAMIC_COLLISION_H

#include "Fixie/Vector3.h"
#include "Physics/DynamicBodyIndex.h"

namespace Physics {
  struct DynamicCollision {
    DynamicBodyIndex bodyA;
    DynamicBodyIndex bodyB;
    Fixie::Vector3 separation;
  };
}

#endif
