#include "Fixie/Vector3.h"
#include "CollisionResolver.h"

namespace Physics {
  void resolveCollisions(const CollisionSet &set, BodyList &bodies) {
    Fixie::Vector3 *positions = bodies.positions;

    for(uint16_t i=0; i<set.dynamics.getCount(); ++i) {
      const DynamicCollision *collision = &set.dynamics.collisions[i];
      Fixie::Vector3 halfSeparation = collision->separation*0.5;

      uint16_t body1Index = bodies.getIndex(collision->body1);
      uint16_t body2Index = bodies.getIndex(collision->body2);

      positions[body1Index] -= halfSeparation;
      positions[body2Index] += halfSeparation;
    }

    for(uint16_t i=0; i<set.statics.getCount(); ++i) {
      const StaticCollision *collision = &set.statics.collisions[i];
      uint16_t dynamicBodyIndex = bodies.getIndex(collision->dynamicBody);
      positions[dynamicBodyIndex] += collision->separation;
    }
  }
}
