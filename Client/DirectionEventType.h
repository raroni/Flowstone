#ifndef CLIENT_DIRECTION_EVENT_TYPE_H
#define CLIENT_DIRECTION_EVENT_TYPE_H

#include <stdint.h>

namespace Client {
  enum class DirectionEventType : uint8_t {
    SteeringStart,
    SteeringStop
  };
}

#endif
