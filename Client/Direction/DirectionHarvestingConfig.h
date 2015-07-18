#ifndef CLIENT_DIRECTION_HARVESTING_CONFIG_H
#define CLIENT_DIRECTION_HARVESTING_CONFIG_H

#include <stdint.h>

namespace Client {
  struct DirectionHarvestingConfig {
    uint8_t work;
    uint8_t idle;
  };
}

#endif
