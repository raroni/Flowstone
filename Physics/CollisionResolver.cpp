#include "Fixie/Vector3.h"
#include "Physics/CollisionSet.h"

namespace Physics {
  void resolveCollisions(CollisionSet &set, Fixie::Vector3 *positions, Fixie::Vector3 *velocities) {
    CollisionSet::DynamicList &dynamics = set.getDynamics();
    for(uint8_t i=0; dynamics.getCount()>i; i++) {
      Fixie::Vector3 halfSeparation = dynamics[i].separation*0.5;

      DynamicBodyIndex bodyA = dynamics[i].bodyA;
      DynamicBodyIndex bodyB = dynamics[i].bodyB;
      positions[bodyA] -= halfSeparation;
      positions[bodyB] += halfSeparation;
    }

    CollisionSet::StaticList &statics = set.getStatics();
    for(uint8_t i=0; statics.getCount()>i; i++) {
      DynamicBodyIndex dynamicBody = statics[i].dynamicBody;
      positions[dynamicBody] += statics[i].separation;
    }
  }
}
