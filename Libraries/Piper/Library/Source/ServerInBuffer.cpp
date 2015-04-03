#include "Piper/ServerInBuffer.h"

namespace Piper {
  ServerInBuffer::ServerInBuffer() :
  messages(Config::Server::inMessageMax, Config::Server::inMessageCapacity, offsets, lengths, storage) { }

  void ServerInBuffer::write(ClientID id, const void *message, uint16_t messageLength) {
    messages.write(message, messageLength);
    ids[messages.getCount()-1] = id;
  }

  uint16_t ServerInBuffer::read(uint16_t position, ClientID *id, const void **message) {
    uint16_t length = messages.read(position, message);
    *id = ids[position];
    return length;
  }

  uint16_t ServerInBuffer::getCount() const {
    return messages.getCount();
  }

  void ServerInBuffer::clear() {
    messages.clear();
  }
}
