#ifndef CONNECTION_H
#define CONNECTION_H

#include "Common/Piper/Client.h"

class ClientConnection {
public:
  void open(const uint8_t *ip, uint16_t port);
  void update(double timeDelta);
private:
  double timeUntilPing = 0;
  enum class State {
    Inactive,
    Connecting,
    Connected
  };
  enum class MessageType : char {
    Ping,
    Pong,
    User
  };
  Piper::Sequence nextID = 0;
  void ping();
  void read();
  void checkPing(double timeDelta);
  void send(Piper::Sequence id, const void *mesage, uint16_t messageLength);
  State state;
  Piper::Client socket;
};

#endif
