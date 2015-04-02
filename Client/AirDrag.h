#ifndef CLIENT_AIR_DRAG_H
#define CLIENT_AIR_DRAG_H

#include <math.h>
#include "Common/Physics/DynamicBodyIndex.h"

namespace Client {
  class AirDrag {
    typedef Physics::DynamicBodyIndex BodyIndex;
    static const uint8_t maxBodies = 128;
    BodyIndex bodyIndices[maxBodies];
    uint8_t bodyIndexCount = 0;
  public:
    void add(BodyIndex index) {
      bodyIndices[bodyIndexCount++] = index;
    }
    void update(const Quanta::Vector3 *velocities, Quanta::Vector3 *forces) const {
      for(uint8_t i=0; bodyIndexCount>i; i++) {
        const Quanta::Vector3 &velocity = velocities[i];
        if(!velocity.isZero()) {
          forces[i] += velocity.getNormalized() * pow(velocity.getLength(), 2) * -1.5;
        }
      }
    }
  };
}

#endif
