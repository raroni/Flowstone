#ifndef PHYSICS_INTEGRATION_H
#define PHYSICS_INTEGRATION_H

#include "Fixie/Util.h"
#include "Fixie/Vector3.h"
#include "Physics/Config.h"

namespace Physics {
  class Integrator {
    const static uint8_t maxBodyIndices = 128;
    DynamicBodyIndex bodyIndices[maxBodyIndices];
    uint8_t offsets[Config::maxDynamicBodies];
    uint8_t bodyCount = 0;
  public:
    void activate(DynamicBodyIndex index) {
      assert(bodyCount != maxBodyIndices);
      bodyIndices[bodyCount] = index;
      offsets[index] = bodyCount;
      bodyCount++;
    }
    void deactivate(DynamicBodyIndex index) {
      bodyCount--;
      uint8_t destroyOffset = offsets[index];
      DynamicBodyIndex lastBodyIndex = bodyIndices[bodyCount];
      offsets[lastBodyIndex] = destroyOffset;
      bodyIndices[destroyOffset] = bodyIndices[bodyCount];
    }
    void integrate(Fixie::Vector3 *positions, Fixie::Vector3 *velocities, Fixie::Vector3 *forces) {
      Fixie::Num stepDuration = static_cast<Fixie::Num>(Config::stepDuration)/Fixie::Num(1000);
      Fixie::Num halfStepDuration = Fixie::Util::halve(stepDuration);
      for(uint8_t i=0; bodyCount>i; i++) {
        DynamicBodyIndex bodyIndex = bodyIndices[i];
        Fixie::Vector3 halfVelocityChange = forces[bodyIndex]*halfStepDuration;
        velocities[bodyIndex] += halfVelocityChange;
        positions[bodyIndex] += velocities[bodyIndex]*stepDuration;
        velocities[bodyIndex] += halfVelocityChange;
        forces[bodyIndex].reset();
      }
    }
  };
}

#endif
