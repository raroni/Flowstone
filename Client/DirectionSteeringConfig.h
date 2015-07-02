#ifndef CLIENT_DIRECTION_STEERING_CONFIG_H
#define CLIENT_DIRECTION_STEERING_CONFIG_H

#include <stdint.h>

namespace Client {
  struct DirectionSteeringConfig {
    uint8_t run;
    uint8_t idle;
  };
}

#endif
