#ifndef PIPER_SERVER_H
#define PIPER_SERVER_H

#include "Piper/Config.h"
#include "Piper/ClientIDPool.h"
#include "Piper/ServerInBuffer.h"
#include "Piper/ServerOutBuffer.h"
#include "Piper/Address.h"
#include "Piper/Socket.h"
#include "Piper/AckSet32.h"
#include "Piper/AckSet128.h"
#include "Piper/Packet.h"

namespace Piper {
  class Server {
  public:
    Server();
    void listen(const Address &address);
    bool readMessage(ClientID *id, const void **message, uint16_t *messageLength);
    Sequence sendMessage(ClientID clientID, const void *message, uint16_t messageLength);
    AckStatus getStatus(ClientID clientID, Sequence sequenceID) const;
    void dispatch();
    void poll();
    void clear();
  private:
    bool findClientID(const Address &address, ClientID &id);
    Sequence createSequenceID(ClientID id);
    Sequence nextSequenceIDs[Config::Server::clientMax];
    Address addresses[Config::Server::clientMax];
    ClientID ids[Config::Server::clientMax];
    AckSet32 inAcks[Config::Server::clientMax];
    AckSet128 outAcks[Config::Server::clientMax];
    uint8_t indices[Config::Server::clientMax];
    ClientIDPool idPool;
    uint16_t clientCount = 0;
    Socket socket;
    ServerInBuffer inBuffer;
    ServerOutBuffer outBuffer;

    uint16_t inBufferPosition = 0;
  };
}

#endif
