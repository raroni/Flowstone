#ifndef PIPER_CLIENT_H
#define PIPER_CLIENT_H

#include "Piper/Config.h"
#include "Piper/Socket.h"
#include "Piper/Address.h"
#include "Piper/Packet.h"
#include "Piper/MessageBuffer.h"
#include "Piper/ClientOutBuffer.h"
#include "Piper/AckSet128.h"
#include "Piper/AckSet32.h"

namespace Piper {
  class Client {
  public:
    Client();
    void setAddress(Address address);
    void poll();
    void clear();
    bool readMessage(const void **message, uint16_t *messageLength);
    Sequence sendMessage(const void *message, uint16_t messageLength);
    void dispatch();
    AckStatus getStatus(Sequence id) const;
  private:
    uint16_t inBufferPosition = 0;
    struct {
      uint16_t offsets[Config::Client::inMessageMax];
      uint16_t lengths[Config::Client::inMessageMax];
      char storage[Config::Client::inMessageCapacity];
    } inData;
    Sequence nextID = 0;
    AckSet32 inAcks;
    AckSet128 outAcks;
    MessageBuffer inBuffer;
    ClientOutBuffer outBuffer;
    Socket socket;
    Address serverAddress;
  };
}

#endif
