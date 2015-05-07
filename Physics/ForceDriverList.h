#ifndef PHYSICS_FORCE_DRIVER_LIST_H
#define PHYSICS_FORCE_DRIVER_LIST_H

#include "Physics/ForceDriverHandle.h"
#include "Physics/ForceDriver.h"
#include "Physics/Config.h"

namespace Physics {
  class ForceDriverList {
  public:
    ForceDriverHandle create(BodyHandle bodyHandle);
    ForceDriver get(ForceDriverHandle handle);
    uint16_t getCount() const;
    BodyHandle bodyHandles[Config::forceDriverMax];
    Fixie::Vector3 forces[Config::forceDriverMax];
    Fixie::Vector3 torques[Config::forceDriverMax];
  private:
    uint16_t count = 0;
  };
}

#endif
