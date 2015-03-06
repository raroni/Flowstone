#include <string.h>
#include "Connection.h"

void Connection::open(const uint8_t *ip, uint16_t port) {
  Piper::Address address;
  memcpy(address.ip, ip, sizeof(uint8_t)*4);
  address.port = port;
  socket.setAddress(address);
}
