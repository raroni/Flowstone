#ifndef SERVER_PING_PONG_H
#define SERVER_PING_PONG_H

namespace ServerPingPong {
  void handlePing(Piper::ClientID clientID, uint8_t pingID);
  void update(double timeDelta);
}

#endif
