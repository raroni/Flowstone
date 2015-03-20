#ifndef CLIENT_CARRIER_H
#define CLIENT_CARRIER_H

#include "Common/Piper/Client.h"

namespace ClientCarrier {
  void setPipe(Piper::Client *pipe);
  void update(double timeDelta);
  void send(const void *message, uint16_t length, float timeout);
}

#endif