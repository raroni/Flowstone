#include <string.h>
#include "ClientConnection.h"

static const double pingInterval = 0.5;

void ClientConnection::open(const uint8_t *ip, uint16_t port) {
  Piper::Address address;
  memcpy(address.ip, ip, sizeof(uint8_t)*4);
  address.port = port;
  socket.setAddress(address);
  state = State::Connecting;
  ping();
}

void ClientConnection::update(double timeDelta) {
  read();
  checkPing(timeDelta);
}

void ClientConnection::read() {
  Piper::Sequence id, ackStart;
  BitSet32 ackBits;
  const void *message = nullptr;
  uint16_t messageLength = 0;

  while(socket.receive(
    id,
    ackStart,
    ackBits,
    message,
    messageLength
  )) {

  }
}

void ClientConnection::checkPing(double timeDelta) {
  timeUntilPing -= timeDelta;
  if(timeUntilPing <= 0) {
    ping();
  }
}

void ClientConnection::send(Piper::Sequence id, const void *message, uint16_t messageLength) {
  BitSet32 bitSet; // dummy

  socket.send(
    id,
    0,
    bitSet,
    message,
    messageLength
  );
}

void ClientConnection::ping() {
  char buffer[] = { static_cast<char>(MessageType::Ping) };
  send(nextID++, buffer, sizeof(buffer));
  timeUntilPing += pingInterval;
}
