#ifndef PHYSICS_STATIC_COLLISION_H
#define PHYSICS_STATIC_COLLISION_H

#include "Fixie/Vector3.h"
#include "Physics/BodyHandle.h"

namespace Physics {
  struct StaticCollision {
    BodyHandle staticBody;
    BodyHandle dynamicBody;
    Fixie::Vector3 separation;
  };
}

#endif
