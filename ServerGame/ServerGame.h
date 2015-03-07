#ifndef SERVER_GAME_H
#define SERVER_GAME_H

#include "ConnectionPool.h"

class ServerGame {
public:
  void initialize();
  void update(double timeDelta);
private:
  ConnectionPool connectionPool;
};

#endif
