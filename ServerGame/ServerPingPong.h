#ifndef SERVER_PING_PONG_H
#define SERVER_PING_PONG_H

#include "Common/Piper/Server.h"

namespace ServerPingPong {
  void configure(Piper::Server *aPipe, Piper::Sequence *aNextSequenceID);
  void handlePing(Piper::ClientID clientID, uint8_t pingID);
  void update(double timeDelta);
}

#endif
