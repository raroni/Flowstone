#ifndef PHYSICS_CONFIG_H
#define PHYSICS_CONFIG_H

#include "SysTime/SysTime.h"

namespace Physics {
  namespace Config {
    const uint16_t bodyMax = 256;
    const uint16_t forceDriverMax = 128;
    const uint16_t velocityDriverMax = 128;
    const uint16_t sphereColliderMax = 128;
    const uint16_t dynamicSphereColliderMax = 64;
    const uint16_t staticSphereColliderMax = 64;
    const uint16_t dynamicCollisionMax = 128;
    const uint16_t staticCollisionMax = 128;
    const SysTime::MSecond16 stepDuration = 30;
  }
}

#endif
