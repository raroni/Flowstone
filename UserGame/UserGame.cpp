#include "ServerGame/ServerGame.h"
#include "UserGame/ClientGame.h"
#include "UserGame/UserGame.h"

namespace UserGame {
  ClientGame clientGame;
  ServerGame *serverGame = nullptr;

  void initialize(uint16_t resolutionWidth, uint16_t resolutionHeight) {
    clientGame.initialize(resolutionWidth, resolutionHeight);
  }

  void update(double timeDelta) {
    clientGame.update(timeDelta);
  }
}
