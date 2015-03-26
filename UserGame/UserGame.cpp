#include "Quanta/Util.h"
#include "UserGame/Platform.h"
#include "Common/GameTime.h"
#include "ServerGame/ServerGame.h"
#include "UserGame/ClientGame.h"
#include "UserGame/UserGame.h"

namespace UserGame {
  static struct {
    const uint16_t width = 800;
    const uint16_t height = 600;
  } resolution;

  ClientGame clientGame;
  ServerGame *serverGame = nullptr;
  static SysTime::USecond64 gameStartTime;
  static SysTime::USecond64 frameStartTime;
  static SysTime::USecond64 frameLastTime;
  const double targetFrameDuration = 1.0/60;
  bool shouldTerminate = false;

  void startServer() {
    serverGame = new ServerGame();
    serverGame->initialize();
  }

  void requestTermination() {
    shouldTerminate = true;
  }

  void initialize() {
    Platform::initialize(resolution.width, resolution.height);
    GameTime::initialize();
    clientGame.initialize(resolution.width, resolution.height);

    gameStartTime = SysTime::get();
    frameLastTime = GameTime::get();
  }

  void terminate() {
    Platform::terminate();
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

    while(!shouldTerminate) {
      Platform::handlePreFrame();
      UserGame::update();
      Platform::handlePostFrame();
    }

    terminate();
  }
}
