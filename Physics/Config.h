#ifndef PHYSICS_CONFIG_H
#define PHYSICS_CONFIG_H

#include "SysTime/SysTime.h"

namespace Physics {
  namespace Config {
    const uint16_t maxDynamicBodies = 128;
    const uint16_t maxStaticBodies = 128;
    const SysTime::MSecond16 stepDuration = 30;
  }
}

#endif
