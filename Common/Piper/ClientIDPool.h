#ifndef PIPER_CLIENT_ID_POOL_H
#define PIPER_CLIENT_ID_POOL_H

#include "Common/Piper/ClientID.h"
#include "Common/Piper/Config.h"

namespace Piper {
  class ClientIDPool {
  public:
    ClientIDPool();
    ClientID obtain();
    void release(ClientID id);
  private:
    ClientID list[Config::Server::clientMax];
    uint8_t count = 0;
  };
}

#endif
