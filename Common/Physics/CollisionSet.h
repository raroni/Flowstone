#ifndef PHYSICS_COLLISION_SET_H
#define PHYSICS_COLLISION_SET_H

#include "Conrad/List.h"
#include "Common/Physics/DynamicCollision.h"
#include "Common/Physics/StaticCollision.h"

namespace Physics {
  class CollisionSet {
  public:
    typedef List<DynamicCollision, 64> DynamicList;
    typedef List<StaticCollision, 64> StaticList;
    DynamicList dynamicCollisions;
    StaticList staticCollisions;
  public:
    DynamicList& getDynamics() {
      return dynamicCollisions;
    }
    StaticList& getStatics() {
      return staticCollisions;
    }
    void clear() {
      dynamicCollisions.clear();
      staticCollisions.clear();
    }
  };
}

#endif
