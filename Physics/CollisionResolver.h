#ifndef PHYSICS_COLLISION_RESOLVER_H
#define PHYSICS_COLLISION_RESOLVER_H

namespace Fixie {
  class Vector3;
}

namespace Physics {
  class CollisionSet;
  void resolveCollisions(CollisionSet &set, Fixie::Vector3 *positions, Fixie::Vector3 *velocities);
}

#endif
