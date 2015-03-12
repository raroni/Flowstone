#include "Common/Piper/ClientOutBuffer.h"

namespace Piper {
  ClientOutBuffer::ClientOutBuffer() :
  messages(
    Config::Client::outMessageMax,
    Config::Client::outMessageCapacity,
    offsets,
    lengths,
    storage
  ) { }

  void ClientOutBuffer::write(Sequence id, const void *message, uint16_t messageLength) {
    messages.write(message, messageLength);
    ids[messages.getCount()-1] = id;
  }

  uint16_t ClientOutBuffer::read(uint16_t position, Sequence *id, const void **message) {
    uint16_t length = messages.read(position, message);
    *id = ids[position];
    return length;
  }

  uint16_t ClientOutBuffer::getCount() const {
    return messages.getCount();
  }

  void ClientOutBuffer::clear() {
    messages.clear();
  }
}
