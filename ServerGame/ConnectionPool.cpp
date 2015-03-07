#include <string.h>
#include "ConnectionPool.h"

#include <stdio.h>

void ConnectionPool::listen(const uint8_t *ip, uint16_t port) {
  Piper::Address address;
  memcpy(address.ip, ip, sizeof(uint8_t)*4);
  address.port = port;
  socket.listen(address);
}

void ConnectionPool::update(double timeDelta) {
  Piper::Packet packet;
  while(socket.receive(packet)) {
    printf("got something.\n");
  }
}
