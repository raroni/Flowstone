#ifndef PHYSICS_STATIC_COLLISION_H
#define PHYSICS_STATIC_COLLISION_H

#include "Fixie/Vector3.h"
#include "Physics/StaticBodyIndex.h"

namespace Physics {
  struct StaticCollision {
    StaticBodyIndex staticBody;
    DynamicBodyIndex dynamicBody;
    Fixie::Vector3 separation;
  };
}

#endif
