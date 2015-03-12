#ifndef SERVER_GAME_H
#define SERVER_GAME_H

#include "Common/Piper/Server.h"

class ServerGame {
public:
  void initialize();
  void update(double timeDelta);
  void readPipe();
private:
  Piper::Server pipe;
  bool clientIDs[Piper::Config::Server::clientMax] = { false };
};

#endif
