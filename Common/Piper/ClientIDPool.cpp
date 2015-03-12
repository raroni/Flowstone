#include "Common/Piper/ClientIDPool.h"

namespace Piper {
  ClientIDPool::ClientIDPool() {
    for(uint8_t i=0; i<maxIDCount; ++i) {
      list[i] = i;
    }
  }

  ClientID ClientIDPool::obtain() {
    ClientID id = list[count];
    count++;
    return id;
  }

  void ClientIDPool::release(ClientID id) {
    list[--count] = id;
  }
}
