#ifndef CLIENT_CARRIER_H
#define CLIENT_CARRIER_H

namespace ClientCarrier {
  void update(double timeDelta);
  void send(const void *message, uint16_t length, float timeout);
}

#endif
