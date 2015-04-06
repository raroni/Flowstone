#ifndef PIPER_SERVER_OUT_BUFFER_H
#define PIPER_SERVER_OUT_BUFFER_H

#include "Piper/Config.h"
#include "Piper/ClientID.h"
#include "Piper/MessageBuffer.h"
#include "Piper/Sequence.h"

namespace Piper {
  class ServerOutBuffer {
  public:
    ServerOutBuffer();
    void write(
      ClientID clientID,
      Sequence sequenceID,
      const void *message,
      uint16_t messageLength
    );
    void read(
      uint16_t position,
      ClientID *clientID,
      Sequence *sequenceID,
      const void **message,
      uint16_t *messageLength
    );
    uint16_t getCount() const;
    void clear();
  private:
    ClientID clientIDs[Config::Server::outMessageMax];
    Sequence sequenceIDs[Config::Server::outMessageMax];
    uint16_t offsets[Config::Server::outMessageMax];
    uint16_t lengths[Config::Server::outMessageMax];
    char storage[Config::Server::outMessageCapacity];
    MessageBuffer messages;
  };
}

#endif
