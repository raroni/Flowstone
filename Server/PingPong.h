#ifndef SERVER_PING_PONG_H
#define SERVER_PING_PONG_H

namespace Server {
  namespace PingPong {
    void handlePing(ClientID clientID, uint8_t pingID);
    void handlePong(ClientID clientID, uint8_t pingID);
    void update(double timeDelta);
  }
}

#endif
