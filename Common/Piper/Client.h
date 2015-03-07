#ifndef PIPER_CLIENT_H
#define PIPER_CLIENT_H

#include "Common/Piper/Socket.h"
#include "Common/Piper/Address.h"
#include "Common/Piper/Packet.h"

namespace Piper {
  class Client {
  public:
    Client();
    void setAddress(Address address);
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
  private:
    Socket socket;
    Address serverAddress;
  };
}

#endif
