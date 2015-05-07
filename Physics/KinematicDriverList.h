#ifndef PHYSICS_KINEMATIC_DRIVER_LIST_H
#define PHYSICS_KINEMATIC_DRIVER_LIST_H

#include "Physics/Config.h"
#include "Physics/BodyHandle.h"
#include "Physics/KinematicDriverHandle.h"

namespace Physics {
  class KinematicDriverList {
  public:
    KinematicDriverHandle create(BodyHandle bodyHandle);
  private:
    BodyHandle bodyHandles[Config::kinematicDriverMax];
    uint16_t count = 0;
  };
}

#endif
