#ifndef SERVER_GAME_CLIENT_ID_POOL_H
#define SERVER_GAME_CLIENT_ID_POOL_H

#include "ServerGameClientID.h"
#include "ServerGameConfig.h"

class ServerGameClientIDPool {
public:
  ServerGameClientIDPool();
  ServerGameClientID obtain();
  void release(ServerGameClientID id);
private:
  ServerGameClientID list[ServerGameConfig::clientMax];
  uint8_t count = 0;
};

#endif
