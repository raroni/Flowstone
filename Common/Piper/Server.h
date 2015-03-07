#ifndef PIPER_SERVER_H
#define PIPER_SERVER_H

#include "Common/Piper/Address.h"
#include "Common/Piper/Socket.h"
#include "Common/Piper/Packet.h"

namespace Piper {
  class Server {
  public:
    Server();
    void listen(const Address &address);
    bool receive(Packet &packet);
  private:
    Socket socket;
  };
}

#endif
