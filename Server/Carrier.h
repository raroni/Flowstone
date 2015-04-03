#ifndef SERVER_CARRIER_H
#define SERVER_CARRIER_H

namespace Server {
  namespace Carrier {
    void update(double timeDelta);
    void send(ClientID clientID, const void *message, uint16_t length, float timeout);
  }
}

#endif
