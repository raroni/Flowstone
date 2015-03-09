#ifndef PIPER_CLIENT_H
#define PIPER_CLIENT_H

#include "Common/Piper/Socket.h"
#include "Common/Piper/Address.h"
#include "Common/Piper/Packet.h"
#include "Common/Piper/MessageBuffer.h"

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
    MessageBuffer inBuffer;
    MessageBuffer outBuffer;
    Sequence outIDs[MessageBuffer::maxCount];
    /*
    bool receive(
      Sequence &id,
      Sequence &ackStart,
      BitSet32 &ackBits,
      const void *message,
      uint16_t messageLength
    );
    void send(
      Sequence id,
      Sequence ackStart,
      const BitSet32 &ackBits,
      const void *message,
      uint16_t messageLength
    );
    */
    Socket socket;
    Address serverAddress;
  };
}

#endif
