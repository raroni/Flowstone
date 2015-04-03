#ifndef CLIENT_PING_PONG_H
#define CLIENT_PING_PONG_H

#include "Misc/GameTime.h"

namespace Client {
  namespace PingPong {
    SysTime::MSecond16 getRTT();
    void update(double timeDelta);
    void handlePong(uint8_t pingID);
    void handlePing(uint8_t pingID);
  }
}

#endif
