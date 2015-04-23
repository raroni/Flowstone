#ifndef PHYSICS_DYNAMIC_COLLISION_H
#define PHYSICS_DYNAMIC_COLLISION_H

#include "Fixie/Vector3.h"
#include "Physics/BodyHandle.h"

namespace Physics {
  struct DynamicCollision {
    BodyHandle bodyA;
    BodyHandle bodyB;
    Fixie::Vector3 separation;
  };
}

#endif
