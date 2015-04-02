#ifndef SERVER_CLIENT_ID_POOL_H
#define SERVER_CLIENT_ID_POOL_H

#include "Server/ClientID.h"
#include "Config.h"

namespace Server {
  class ClientIDPool {
  public:
    ClientIDPool();
    ClientID obtain();
    void release(ClientID id);
  private:
    ClientID list[Config::clientMax];
    uint8_t count = 0;
  };
}

#endif
