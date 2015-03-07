#ifndef CONNECTION_POOL_H
#define CONNECTION_POOL_H

#include "Common/Piper/Server.h"

class ConnectionPool {
public:
  void listen(const uint8_t *ip, uint16_t port);
  void update(double timeDelta);
private:
  Piper::Server socket;
};

#endif
