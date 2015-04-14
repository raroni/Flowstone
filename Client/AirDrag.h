#ifndef CLIENT_AIR_DRAG_H
#define CLIENT_AIR_DRAG_H

#include <math.h>
#include "Physics/DynamicBodyIndex.h"

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
    void update(const Fixie::Vector3 *velocities, Fixie::Vector3 *forces) const {
      for(uint8_t i=0; bodyIndexCount>i; i++) {
        const Fixie::Vector3 &velocity = velocities[i];
        Fixie::Num speed = velocity.calcLength();
        if(speed != Fixie::Num(0)) {
          Fixie::Vector3 direction = velocity/speed;
          forces[i] += direction*speed*speed*Fixie::Num(-1.5);
        }
      }
    }
  };
}

#endif
