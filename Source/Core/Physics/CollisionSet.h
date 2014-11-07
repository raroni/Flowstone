#ifndef PHYSICS_COLLISION_SET_H
#define PHYSICS_COLLISION_SET_H

#include "Conrad/List.h"
#include "Core/Physics/DynamicCollision.h"

namespace Physics {
  class CollisionSet {
  public:
    typedef List<DynamicCollision, 64> DynamicList;
     DynamicList dynamicCollisions;
  public:
    DynamicList& getDynamics() {
      return dynamicCollisions;
    }
    void clear() {
      dynamicCollisions.clear();
    }
  };
}

#endif
