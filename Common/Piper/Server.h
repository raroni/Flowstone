#ifndef PIPER_SERVER_H
#define PIPER_SERVER_H

#include "Common/Piper/Address.h"
#include "Common/Piper/Socket.h"

namespace Piper {
  class Server {
  public:
    Server();
    void listen(const Address &address);
  private:
    Socket socket;
  };
}

#endif
