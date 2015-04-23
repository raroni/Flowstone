#ifndef PHYSICS_COLLISION_SET_H
#define PHYSICS_COLLISION_SET_H

#include "Physics/Config.h"
#include "Physics/CollisionSet.h"
#include "Physics/DynamicCollision.h"
#include "Physics/StaticCollision.h"

namespace Physics {
  struct CollisionSet {
    struct {
      DynamicCollision values[Config::dynamicCollisionMax];
      uint16_t count = 0;
    } dynamics;
    struct {
      StaticCollision values[Config::staticCollisionMax];
      uint16_t count = 0;
    } statics;
    void clear() {
      dynamics.count = 0;
      statics.count = 0;
    }
  };
}

#endif
