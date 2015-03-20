#ifndef PING_PONG_H
#define PING_PONG_H

#include "Common/GameTime.h"
#include "Common/Piper/Client.h"

namespace PingPong {
  GameTime::MSecond16 getRTT();
  void setPipe(Piper::Client &pipe);
  void update(double timeDelta);
  void handlePong(uint8_t pingID);
}

#endif
