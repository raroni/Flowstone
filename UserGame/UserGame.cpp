#include "Quanta/Util.h"
#include "Common/GameTime.h"
#include "ServerControl.h"
#include "UserGame/ClientGame.h"
#include "UserGame/UserGame.h"
#include "SysThread.h"
#include "SysTime/SysTime.h"

namespace UserGame {
  static SysTime::USecond64 gameStartTime;
  static SysTime::USecond64 frameStartTime;
  static SysTime::USecond64 frameLastTime;
  const double targetFrameDuration = 1.0/500;

  void startServer() {
    ServerControl::requestInit();
  }

  void stopServer() {
    ServerControl::requestTermination();
  }

  void requestTermination() {
    ClientGame::requestTermination();
  }

  void initialize() {
    ServerControl::initialize();
    GameTime::initialize();
    ClientGame::initialize();

    gameStartTime = SysTime::get();
    frameLastTime = GameTime::get();
  }

  void terminate() {
    ClientGame::terminate();
    ServerControl::terminate();
  }

  void update() {
    frameStartTime = GameTime::get();
    double timeDelta = 0.000001*(frameStartTime-frameLastTime);

    ClientGame::update(timeDelta);
    ServerControl::update();

    SysTime::USecond64 now = GameTime::get();
    SysTime::USecond64 duration = now-frameStartTime;
    double rest = targetFrameDuration-0.000001*duration;
    SysTime::sleep(Quanta::max(rest*1000000.0, 0.0));
    frameLastTime = frameStartTime;
  }

  void run() {
    initialize();

    while(!ClientGame::shouldTerminate()) {
      update();
    }

    terminate();
  }
}
