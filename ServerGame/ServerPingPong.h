#ifndef SERVER_PING_PONG_H
#define SERVER_PING_PONG_H

#include "Common/Piper/Server.h"

namespace ServerPingPong {
  void setPipe(Piper::Server *aPipe);
  void handlePing(Piper::ClientID id);
  void update(double timeDelta);
}

#endif
