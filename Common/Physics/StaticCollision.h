#ifndef PHYSICS_STATIC_COLLISION_H
#define PHYSICS_STATIC_COLLISION_H

#include "Quanta/Math/Vector3.h"
#include "Common/Physics/StaticBodyIndex.h"

namespace Physics {
  struct StaticCollision {
    StaticBodyIndex staticBody;
    DynamicBodyIndex dynamicBody;
    Quanta::Vector3 separation;
  };
}

#endif
