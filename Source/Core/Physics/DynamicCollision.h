#ifndef PHYSICS_COLLISION_H
#define PHYSICS_COLLISION_H

#include "Quanta/Math/Vector3.h"

namespace Physics {
  struct DynamicCollision {
    DynamicBodyIndex bodyA;
    DynamicBodyIndex bodyB;
    Quanta::Vector3 separation;
  };
}

#endif
