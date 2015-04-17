#ifndef SIMULATION_CONFIG_H
#define SIMULATION_CONFIG_H

#include "SysTime/SysTime.h"
#include "Simulation/ComponentType.h"

namespace Simulation {
  namespace Config {
    const SysTime::MSecond16 tickDuration = 30;
    const uint16_t entityMax = 512;
    const uint8_t componentMax = static_cast<uint8_t>(ComponentType::Count);
  }
}

#endif
