#ifndef CONNECTION_H
#define CONNECTION_H

#include "Common/Piper/Client.h"

class Connection {
public:
  void open(const uint8_t *ip, uint16_t port);
private:
  Piper::Client socket;
};

#endif
