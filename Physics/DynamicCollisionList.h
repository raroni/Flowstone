#ifndef PHYSICS_DYNAMIC_COLLISION_LIST_H
#define PHYSICS_DYNAMIC_COLLISION_LIST_H

#include "Physics/Config.h"
#include "Physics/DynamicCollision.h"

namespace Physics {
  class DynamicCollisionList {
  public:
    void add(BodyHandle bodyHandle1, BodyHandle bodyHandle2, Fixie::Vector3 &separation) {
      collisions[count].body1 = bodyHandle1;
      collisions[count].body2 = bodyHandle2;
      collisions[count].separation = separation;
      count++;
    }
    void clear() {
      count = 0;
    }
    bool isFull() {
      return count == Config::dynamicCollisionMax;
    }
    uint16_t getCount() const {
      return count;
    }
    DynamicCollision collisions[Config::dynamicCollisionMax];
  private:
    uint16_t count = 0;
  };
}

#endif
