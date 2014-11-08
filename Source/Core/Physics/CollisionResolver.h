#ifndef PHYSICS_COLLISION_RESOLVER_H
#define PHYSICS_COLLISION_RESOLVER_H

namespace Quanta {
  class Vector3;
}

namespace Physics {
  class CollisionSet;
  void resolveCollisions(CollisionSet &set, Quanta::Vector3 *positions, Quanta::Vector3 *velocities);
}

#endif
