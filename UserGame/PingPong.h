#ifndef PING_PONG_H
#define PING_PONG_H

#include "Common/GameTime.h"

namespace PingPong {
  GameTime::MSecond16 getRTT();
  void update(double timeDelta);
  void handlePong(uint8_t pingID);
}

#endif
