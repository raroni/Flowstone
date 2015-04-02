#include "SysThread.h"
#include "SysKey/SysKey.h"
#include "SysTime/SysTime.h"
#include "Quanta/Util.h"
#include "Common/GameTime.h"
#include "Common/MessageType.h"
#include "ServerControl.h"
#include "Rendering/Renderer.h"
#include "Keyboard.h"
#include "MainFlow/Manager.h"
#include "ClientPlatform.h"
#include "PresentationSync.h"
#include "Presentation.h"
#include "ClientNet.h"
#include "PingPong.h"
#include "ClientCarrier.h"
#include "PresentationSync.h"
#include "Client/Game.h"

namespace Client {
  namespace Game {
    static SysTime::USecond64 gameStartTime;
    static SysTime::USecond64 frameStartTime;
    static SysTime::USecond64 frameLastTime;
    const double targetFrameDuration = 1.0/500;

    SysThread::Thread presenter;
    bool terminationRequested = false;
    SysThread::Mutex terminateMutex;
    struct {
      const uint16_t width = 800;
      const uint16_t height = 600;
    } resolution;
    void readNet();
    void updateKeyboard();
    Keyboard keyboard;
    Rendering::Renderer renderer;
    MainFlow::Manager flow;

    void updateKeyboard() {
      SysKey::Event event;
      while(SysKey::pollEvent(event)) {
        if(event.type == SysKey::EventType::Down) {
          keyboard.handleDown(event.key);
        } else {
          keyboard.handleUp(event.key);
        }
      }
    }

    bool shouldTerminate() {
      SysThread::lock(&terminateMutex);
      bool copy = terminationRequested;
      SysThread::unlock(&terminateMutex);
      return copy;
    }

    void requestTermination() {
      SysThread::lock(&terminateMutex);
      terminationRequested = true;
      SysThread::unlock(&terminateMutex);
    }

    void readNet() {
      ClientNet::poll();

      MessageType type;
      const void *message = nullptr;
      uint16_t messageLength = 0;

      while(ClientNet::readMessage(&type, &message, &messageLength)) {
        switch(type) {
          case MessageType::Pong: {
            if(messageLength == 1) {
              uint8_t pingID = *static_cast<const uint8_t*>(message);
              PingPong::handlePong(pingID);
            }
            break;
          }
          case MessageType::Ping: {
            if(messageLength == 1) {
              uint8_t pingID = *static_cast<const uint8_t*>(message);
              PingPong::handlePing(pingID);
            }
            break;
          }
          default:
            //printf("Client got something unknown.\n");
            break;
        }
      }
      ClientNet::clear();
    }

    void initialize() {
      ServerControl::initialize();
      GameTime::initialize();

      ClientPlatform::initialize(resolution.width, resolution.height);
      SysThread::initMutex(&terminateMutex);
      PresentationSync::initialize();
      SysThread::init(&presenter, Presentation::run);

      renderer.initialize();
      renderer.updateResolution({ resolution.width, resolution.height });
      flow.initialize(renderer);

      ClientNet::initialize();
      Piper::Address address;
      address.ip[0] = 127;
      address.ip[1] = 0;
      address.ip[2] = 0;
      address.ip[3] = 1;
      address.port = 4242;
      ClientNet::setAddress(address);

      // dummy
      ServerControl::requestInit();

      gameStartTime = SysTime::get();
      frameLastTime = GameTime::get();
    }

    void terminate() {
      ServerControl::requestTermination();
      SysThread::join(&presenter);
      PresentationSync::terminate();
      SysThread::destroyMutex(&terminateMutex);
      ClientPlatform::terminate();

      ServerControl::terminate();
    }

    void update() {
      frameStartTime = GameTime::get();
      double timeDelta = 0.000001*(frameStartTime-frameLastTime);

      ClientPlatform::handlePreFrame();

      readNet();
      PingPong::update(timeDelta);

      updateKeyboard();
      flow.update(timeDelta, keyboard);
      ClientCarrier::update(timeDelta);

      if(PresentationSync::shouldDraw()) {
        renderer.draw();
        PresentationSync::handleDrawCompletion();
      }

      ClientNet::dispatch();

      ClientPlatform::handlePostFrame();

      ServerControl::update();

      SysTime::USecond64 now = GameTime::get();
      SysTime::USecond64 duration = now-frameStartTime;
      double rest = targetFrameDuration-0.000001*duration;
      SysTime::sleep(Quanta::max(rest*1000000.0, 0.0));
      frameLastTime = frameStartTime;
    }

    void run() {
      initialize();

      while(!shouldTerminate()) {
        update();
      }

      terminate();
    }
  }
}
