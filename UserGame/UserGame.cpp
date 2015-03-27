#include "Quanta/Util.h"
#include "Common/GameTime.h"
#include "ServerGame/ServerGame.h"
#include "UserGame/ClientGame.h"
#include "UserGame/UserGame.h"
#include "SysThread.h"
#include "SysTime/SysTime.h"

namespace UserGame {
  ClientGame clientGame;
  ServerGame *serverGame = nullptr;
  static SysTime::USecond64 gameStartTime;
  static SysTime::USecond64 frameStartTime;
  static SysTime::USecond64 frameLastTime;
  const double targetFrameDuration = 1.0/500;
  ClientGame *stupidHack = nullptr;

  void startServer() {
    serverGame = new ServerGame();
    serverGame->initialize();
  }

  void requestTermination() {
    clientGame.requestTermination();
  }

  void initialize() {
    stupidHack = &clientGame;
    GameTime::initialize();
    clientGame.initialize();

    gameStartTime = SysTime::get();
    frameLastTime = GameTime::get();
  }

  void terminate() {
    clientGame.terminate();
  }

  void update() {
    frameStartTime = GameTime::get();
    double timeDelta = 0.000001*(frameStartTime-frameLastTime);

    if(serverGame != nullptr) {
      serverGame->update(timeDelta);
    }
    clientGame.update(timeDelta);

    SysTime::USecond64 now = GameTime::get();
    SysTime::USecond64 duration = now-frameStartTime;
    double rest = targetFrameDuration-0.000001*duration;
    SysTime::sleep(Quanta::max(rest*1000000.0, 0.0));
    frameLastTime = frameStartTime;
  }

  void run() {
    initialize();

    while(!clientGame.shouldTerminate()) {
      update();
    }

    terminate();
  }
}
