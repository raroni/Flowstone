#ifndef SERVER_GAME_H
#define SERVER_GAME_H

#include "Common/Piper/Config.h"

class ServerGame {
public:
  void initialize();
  void update(double timeDelta);
  void readPipe();
private:
  bool clientIDs[Piper::Config::Server::clientMax] = { false };
};

#endif
