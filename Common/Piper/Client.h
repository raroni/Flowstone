#ifndef PIPER_CLIENT_H
#define PIPER_CLIENT_H

#include "Common/Piper/Config.h"
#include "Common/Piper/Socket.h"
#include "Common/Piper/Address.h"
#include "Common/Piper/Packet.h"
#include "Common/Piper/MessageBuffer.h"
#include "Common/Piper/ClientOutBuffer.h"

namespace Piper {
  class Client {
  public:
    Client();
    void setAddress(Address address);
    void poll();
    void clear();
    bool readMessage(const void **message, uint16_t *messageLength);
    void sendMessage(Sequence id, const void *message, uint16_t messageLength);
    void dispatch();
    uint16_t createID();
  private:
    uint16_t nextID = 0;
    uint16_t inBufferPosition = 0;
    struct {
      uint16_t offsets[Config::Client::inMessageMax];
      uint16_t lengths[Config::Client::inMessageMax];
      char storage[Config::Client::inMessageCapacity];
    } inData;
    MessageBuffer inBuffer;
    ClientOutBuffer outBuffer;
    Socket socket;
    Address serverAddress;
  };
}

#endif
