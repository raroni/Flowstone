#ifndef PHYSICS_DYNAMIC_COLLISION_H
#define PHYSICS_DYNAMIC_COLLISION_H

#include "Quanta/Math/Vector3.h"
#include "Common/Physics/DynamicBodyIndex.h"

namespace Physics {
  struct DynamicCollision {
    DynamicBodyIndex bodyA;
    DynamicBodyIndex bodyB;
    Quanta::Vector3 separation;
  };
}

#endif
