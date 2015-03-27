#include "Quanta/Util.h"
#include "UserGame/ClientPlatform.h"
#include "Common/GameTime.h"
#include "ServerGame/ServerGame.h"
#include "UserGame/ClientGame.h"
#include "UserGame/UserGame.h"
#include "PresentationSync.h"
#include "Presentation.h"
#include "SysThread.h"
#include "SysTime/SysTime.h"

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
  const double targetFrameDuration = 1.0/500;
  bool terminationRequested = false;
  SysThread::Mutex terminateMutex;
  SysThread::Thread presenter;

  bool shouldTerminate() {
    SysThread::lock(&terminateMutex);
    bool copy = terminationRequested;
    SysThread::unlock(&terminateMutex);
    return copy;
  }

  void startServer() {
    serverGame = new ServerGame();
    serverGame->initialize();
  }

  void requestTermination() {
    SysThread::lock(&terminateMutex);
    terminationRequested = true;
    SysThread::unlock(&terminateMutex);
  }

  void initialize() {
    PresentationSync::initialize();
    ClientPlatform::initialize(resolution.width, resolution.height);
    GameTime::initialize();
    clientGame.initialize(resolution.width, resolution.height);

    gameStartTime = SysTime::get();
    frameLastTime = GameTime::get();

    SysThread::initMutex(&terminateMutex);
    SysThread::init(&presenter, Presentation::run);
  }

  void terminate() {
    SysThread::join(&presenter);
    SysThread::destroyMutex(&terminateMutex);
    ClientPlatform::terminate();
    PresentationSync::terminate();
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

    while(!shouldTerminate()) {
      ClientPlatform::handlePreFrame();
      UserGame::update();
      ClientPlatform::handlePostFrame();
    }

    terminate();
  }
}
