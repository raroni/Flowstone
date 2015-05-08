#ifndef SIMULATION_CONFIG_H
#define SIMULATION_CONFIG_H

#include "SysTime/SysTime.h"
#include "Simulation/ComponentType.h"

namespace Simulation {
  namespace Config {
    const SysTime::MSecond16 tickDuration = 30;
    const uint16_t entityMax = 512;
    const uint8_t componentMax = static_cast<uint8_t>(ComponentType::Count);
    const uint16_t resourceMax = 256;
    const uint16_t steeringMax = 128;
    const uint16_t pathfinderMax = 128;
    const uint16_t dragMax = 128;
    const uint16_t mapWidthMax = 128;
    const uint16_t mapHeightMax = 128;
    const uint32_t mapSizeMax = mapWidthMax*mapHeightMax;
    const uint16_t aStarCostBucketCount = 128;
  }
}

#endif
