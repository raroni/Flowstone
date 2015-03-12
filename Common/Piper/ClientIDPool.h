#ifndef PIPER_CLIENT_ID_POOL_H
#define PIPER_CLIENT_ID_POOL_H

#include "Common/Piper/ClientID.h"

namespace Piper {
  class ClientIDPool {
  public:
    ClientIDPool();
    ClientID obtain();
    void release(ClientID id);
  private:
    const static uint8_t maxIDCount = 16;
    ClientID list[maxIDCount];
    uint8_t count = 0;
  };
}

#endif
