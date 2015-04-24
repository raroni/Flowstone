#ifndef SIMULATION_CONFIG_H
#define SIMULATION_CONFIG_H

#include "SysTime/SysTime.h"
#include "Simulation/Database/ComponentType.h"

namespace Simulation {
  namespace Config {
    const SysTime::MSecond16 tickDuration = 30;
    const uint16_t entityMax = 512;
    const uint8_t componentMax = static_cast<uint8_t>(ComponentType::Count);
    const uint16_t resourceMax = 256;
    const uint16_t steeringMax = 128;
  }
}

#endif
