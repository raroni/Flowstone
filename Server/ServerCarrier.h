#ifndef SERVER_CARRIER_H
#define SERVER_CARRIER_H

namespace ServerCarrier {
  void update(double timeDelta);
  void send(ServerGameClientID clientID, const void *message, uint16_t length, float timeout);
}

#endif
