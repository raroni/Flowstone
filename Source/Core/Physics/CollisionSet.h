#ifndef PHYSICS_COLLISION_SET_H
#define PHYSICS_COLLISION_SET_H

#include "Core/Physics/Collision.h"

namespace Physics {
  class CollisionSet {
  public:
    const static uint8_t maxCount = 64;
    Collision collisions[maxCount];
    uint8_t count = 0;
    void add(Collision collision) {
      collisions[count++] = collision;
    }
    bool full() {
      return count == maxCount;
    }
    uint8_t getCount() {
      return count;
    }
    const Collision& operator[](const uint8_t index) {
      assert(index < count);
      return collisions[index];
    }
    void clear() {
      count = 0;
    }
  };
}

#endif
