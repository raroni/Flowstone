#include "Common/Piper/ServerBuffer.h"

namespace Piper {
  ServerBuffer::ServerBuffer(
    uint16_t maxCount,
    uint16_t capacity,
    ClientID *ids,
    uint16_t *offsets,
    uint16_t *lengths,
    void *storage
  ) :
  messages(maxCount, capacity, offsets, lengths, storage),
  ids(ids) { }

  void ServerBuffer::write(ClientID id, const void *message, uint16_t messageLength) {
    messages.write(message, messageLength);
    ids[messages.getCount()-1] = id;
  }

  uint16_t ServerBuffer::read(uint16_t position, ClientID *id, const void **message) {
    uint16_t length = messages.read(position, message);
    *id = ids[position];
    return length;
  }

  uint16_t ServerBuffer::getCount() const {
    return messages.getCount();
  }

  void ServerBuffer::clear() {
    messages.clear();
  }
}
