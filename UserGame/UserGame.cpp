#include "Common/GameTime.h"
#include "ServerGame/ServerGame.h"
#include "UserGame/ClientGame.h"
#include "UserGame/UserGame.h"

namespace UserGame {
  ClientGame clientGame;
  ServerGame *serverGame = nullptr;

  void initialize(uint16_t resolutionWidth, uint16_t resolutionHeight) {
    GameTime::initialize();
    clientGame.initialize(resolutionWidth, resolutionHeight);
  }

  void update(double timeDelta) {
    if(serverGame != nullptr) {
      serverGame->update(timeDelta);
    }
    clientGame.update(timeDelta);
  }

  void startServer() {
    serverGame = new ServerGame();
    serverGame->initialize();
  }
}
