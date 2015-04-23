#include "Fixie/Vector3.h"
#include "CollisionResolver.h"

namespace Physics {
  void resolveCollisions(const CollisionSet &set, BodyList &bodies) {
    Fixie::Vector3 *positions = bodies.positions;

    for(uint16_t i=0; i<set.dynamics.count; ++i) {
      const DynamicCollision *collision = &set.dynamics.values[i];
      Fixie::Vector3 halfSeparation = collision->separation*0.5;

      uint16_t bodyAIndex = bodies.getIndex(collision->bodyA);
      uint16_t bodyBIndex = bodies.getIndex(collision->bodyB);

      positions[bodyAIndex] -= halfSeparation;
      positions[bodyBIndex] += halfSeparation;
    }

    for(uint16_t i=0; i<set.statics.count; ++i) {
      const StaticCollision *collision = &set.statics.values[i];
      uint16_t dynamicBodyIndex = bodies.getIndex(collision->dynamicBody);
      positions[dynamicBodyIndex] += collision->separation;
    }
  }
}
