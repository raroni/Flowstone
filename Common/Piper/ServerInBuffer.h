#ifndef PIPER_SERVER_BUFFER_H
#define PIPER_SERVER_BUFFER_H

#include "Common/Piper/Config.h"
#include "Common/Piper/MessageBuffer.h"
#include "Common/Piper/ClientID.h"

namespace Piper {
  class ServerInBuffer {
  public:
    ServerInBuffer();
    void write(ClientID id, const void *message, uint16_t messageLength);
    uint16_t read(uint16_t position, ClientID *id, const void **message);
    uint16_t getCount() const;
    void clear();
  private:
    uint16_t offsets[Config::Server::inMessageMax];
    uint16_t lengths[Config::Server::inMessageMax];
    ClientID ids[Config::Server::inMessageMax];
    char storage[Config::Server::inMessageCapacity];
    MessageBuffer messages;
  };
}

#endif
