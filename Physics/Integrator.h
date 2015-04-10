#ifndef PHYSICS_INTEGRATION_H
#define PHYSICS_INTEGRATION_H

#include "Quanta/Math/Vector3.h"
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
    void integrate(Quanta::Vector3 *positions, Quanta::Vector3 *velocities, Quanta::Vector3 *forces) {
      double stepDuration = static_cast<double>(Config::stepDuration)/1000.0;
      double halfStepDuration = stepDuration*0.5;
      for(uint8_t i=0; bodyCount>i; i++) {
        DynamicBodyIndex bodyIndex = bodyIndices[i];
        Quanta::Vector3 halfVelocityChange = forces[bodyIndex]*halfStepDuration;
        velocities[bodyIndex] += halfVelocityChange;
        positions[bodyIndex] += velocities[bodyIndex]*stepDuration;
        velocities[bodyIndex] += halfVelocityChange;
        forces[bodyIndex].reset();
      }
    }
  };
}

#endif
