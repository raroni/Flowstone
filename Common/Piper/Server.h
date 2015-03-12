#ifndef PIPER_SERVER_H
#define PIPER_SERVER_H

#include "Common/Piper/Config.h"
#include "Common/Piper/ClientIDPool.h"
#include "Common/Piper/ServerInBuffer.h"
#include "Common/Piper/ServerOutBuffer.h"
#include "Common/Piper/Address.h"
#include "Common/Piper/Socket.h"
#include "Common/Piper/Packet.h"

namespace Piper {
  class Server {
  public:
    Server();
    void listen(const Address &address);
    bool readMessage(ClientID *id, const void **message, uint16_t *messageLength);
    void sendMessage(ClientID clientID, Sequence sequenceID, const void *message, uint16_t messageLength);
    bool findClientID(const Address &address, ClientID &id);
    void dispatch();
    void poll();
    void clear();
  private:
    Address addresses[Config::Server::clientMax];
    ClientID ids[Config::Server::clientMax];
    uint8_t indices[Config::Server::clientMax];
    ClientIDPool idPool;
    uint16_t clientCount = 0;
    Socket socket;
    // todo: move this data into ServerInBuffer, no need to put it here
    struct {
      uint16_t offsets[Config::Server::inMessageMax];
      uint16_t lengths[Config::Server::inMessageMax];
      ClientID ids[Config::Server::inMessageMax];
      char storage[Config::Server::inMessageCapacity];
    } inData;
    ServerInBuffer inBuffer;
    ServerOutBuffer outBuffer;

    uint16_t inBufferPosition = 0;
  };
}

#endif
