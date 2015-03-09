#ifndef PING_PONG_H
#define PING_PONG_H

#include "Common/Piper/Client.h"

namespace PingPong {
  void setPipe(Piper::Client &pipe);
  void update(double timeDelta);
}

#endif
