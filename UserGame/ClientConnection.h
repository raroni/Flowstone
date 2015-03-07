#ifndef CONNECTION_H
#define CONNECTION_H

#include "Common/Piper/Client.h"

class ClientConnection {
public:
  void open(const uint8_t *ip, uint16_t port);
  void update(double timeDelta);
private:
  Piper::Client socket;
};

#endif
