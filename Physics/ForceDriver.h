#ifndef PHYSICS_FORCE_DRIVER_H
#define PHYSICS_FORCE_DRIVER_H

#include "Physics/BodyHandle.h"
#include "Fixie/Vector3.h"

namespace Physics {
  struct ForceDriver {
    Fixie::Vector3 *force = nullptr;
    Physics::BodyHandle bodyHandle;
  };
}

#endif
