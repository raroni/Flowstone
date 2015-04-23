#ifndef PHYSICS_COLLISION_SET_H
#define PHYSICS_COLLISION_SET_H

#include "Physics/DynamicCollisionList.h"
#include "Physics/StaticCollisionList.h"

namespace Physics {
  struct CollisionSet {
    DynamicCollisionList dynamics;
    StaticCollisionList statics;
    void clear() {
      dynamics.clear();
      statics.clear();
    }
  };
}

#endif
