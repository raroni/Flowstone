#include "Common/Piper/ServerOutBuffer.h"

namespace Piper {
  ServerOutBuffer::ServerOutBuffer() :
  messages(Config::Server::outMessageMax, Config::Server::outMessageCapacity, offsets, lengths, storage) {

  }

  uint16_t ServerOutBuffer::getCount() const {
    return messages.getCount();
  }

  void ServerOutBuffer::write(
    ClientID clientID,
    Sequence sequenceID,
    const void *message,
    uint16_t messageLength
  ) {
    messages.write(message, messageLength);
    uint16_t count = messages.getCount()-1;
    clientIDs[count] = clientID;
    sequenceIDs[count] = sequenceID;
  }

  void ServerOutBuffer::clear() {
    messages.clear();
  }

  void ServerOutBuffer::read(
    uint16_t position,
    ClientID *clientID,
    Sequence *sequenceID,
    const void **message,
    uint16_t *messageLength
  ) {
    *messageLength = messages.read(position, message);
    *clientID = clientIDs[position];
    *sequenceID = sequenceIDs[position];
  }
}
