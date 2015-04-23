#ifndef PHYSICS_VELOCITY_DRIVER_LIST_H
#define PHYSICS_VELOCITY_DRIVER_LIST_H

#include "Physics/Config.h"
#include "Physics/BodyHandle.h"
#include "Physics/VelocityDriverHandle.h"

namespace Physics {
  class VelocityDriverList {
  public:
    VelocityDriverHandle create(BodyHandle bodyHandle);
  private:
    BodyHandle bodyHandles[Config::velocityDriverMax];
    uint16_t count = 0;
  };
}

#endif
