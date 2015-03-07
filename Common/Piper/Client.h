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
    bool receive(Packet &packet);
    void send(const Packet &packet);
  private:
    Socket socket;
    Address serverAddress;
  };
}

#endif
