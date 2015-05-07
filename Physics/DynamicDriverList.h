#ifndef PHYSICS_DYNAMIC_DRIVER_LIST_H
#define PHYSICS_DYNAMIC_DRIVER_LIST_H

#include "Physics/DynamicDriverHandle.h"
#include "Physics/DynamicDriver.h"
#include "Physics/Config.h"

namespace Physics {
  class DynamicDriverList {
  public:
    DynamicDriverHandle create(BodyHandle bodyHandle);
    DynamicDriver get(DynamicDriverHandle handle);
    uint16_t getCount() const;
    BodyHandle bodyHandles[Config::dynamicDriverMax];
    Fixie::Vector3 forces[Config::dynamicDriverMax];
    Fixie::Vector3 torques[Config::dynamicDriverMax];
  private:
    uint16_t count = 0;
  };
}

#endif
