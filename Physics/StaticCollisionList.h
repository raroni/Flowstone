#ifndef PHYSICS_STATIC_COLLISION_LIST_H
#define PHYSICS_STATIC_COLLISION_LIST_H

#include "Physics/Config.h"
#include "Physics/StaticCollision.h"

namespace Physics {
  class StaticCollisionList {
  public:
    void add(BodyHandle bodyHandle1, BodyHandle bodyHandle2, Fixie::Vector3 &separation) {
      collisions[count].staticBody = bodyHandle1;
      collisions[count].dynamicBody = bodyHandle2;
      collisions[count].separation = separation;
      count++;
    }
    void clear() {
      count = 0;
    }
    bool isFull() {
      return count == Config::staticCollisionMax;
    }
    uint16_t getCount() const {
      return count;
    }
    StaticCollision collisions[Config::staticCollisionMax];
  private:
    uint16_t count = 0;
  };
}

#endif
