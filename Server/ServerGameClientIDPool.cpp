#include "ServerGameClientIDPool.h"

ServerGameClientIDPool::ServerGameClientIDPool() {
  for(uint8_t i=0; i<ServerGameConfig::clientMax; ++i) {
    list[i] = i;
  }
}

ServerGameClientID ServerGameClientIDPool::obtain() {
  ServerGameClientID id = list[count];
  count++;
  return id;
}

void ServerGameClientIDPool::release(ServerGameClientID id) {
  list[--count] = id;
}
