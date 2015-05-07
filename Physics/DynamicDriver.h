#ifndef PHYSICS_DYNAMIC_DRIVER_H
#define PHYSICS_DYNAMIC_DRIVER_H

#include "Physics/BodyHandle.h"
#include "Fixie/Vector3.h"

namespace Physics {
  struct DynamicDriver {
    Fixie::Vector3 *force = nullptr;
    Fixie::Vector3 *torque = nullptr;
    Physics::BodyHandle bodyHandle;
  };
}

#endif
