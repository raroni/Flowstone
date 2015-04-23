#ifndef PHYSICS_COLLISION_RESOLVER_H
#define PHYSICS_COLLISION_RESOLVER_H

#include "Physics/BodyList.h"
#include "Physics/CollisionSet.h"

namespace Physics {
  void resolveCollisions(const CollisionSet &set, BodyList &bodies);
}

#endif
