#include "SysThread.h"
#include "SysKey/SysKey.h"
#include "SysTime/SysTime.h"
#include "Quanta/Util.h"
#include "Misc/GameTime.h"
#include "Misc/MessageType.h"
#include "Rendering/Renderer.h"
#include "Client/ServerControl.h"
#include "Client/Keyboard.h"
#include "Client/MainFlow/Manager.h"
#include "Client/Platform.h"
#include "Client/Net.h"
#include "Client/PingPong.h"
#include "Client/Carrier.h"
#include "Client/Game.h"

namespace Client {
  namespace Game {
    static SysTime::USecond64 frameLastTime;
    const double targetFrameDuration = 1.0/60;
    bool terminationRequested = false;
    SysThread::Mutex terminateMutex;
    struct {
      const uint16_t width = 600;
      const uint16_t height = 400;
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
      Net::poll();

      MessageType type;
      const void *message = nullptr;
      uint16_t messageLength = 0;

      while(Net::readMessage(&type, &message, &messageLength)) {
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
      Net::clear();
    }

    void initialize() {
      ServerControl::initialize();
      GameTime::initialize();

      Platform::initialize(resolution.width, resolution.height);
      SysThread::initMutex(&terminateMutex);

      renderer.initialize();
      renderer.updateResolution({ resolution.width, resolution.height });
      flow.initialize(renderer);

      Net::initialize();
      Piper::Address address;
      address.ip[0] = 127;
      address.ip[1] = 0;
      address.ip[2] = 0;
      address.ip[3] = 1;
      address.port = 4242;
      Net::setAddress(address);

      // dummy
      ServerControl::requestInit();

      frameLastTime = GameTime::get();
    }

    void terminate() {
      ServerControl::requestTermination();
      SysThread::destroyMutex(&terminateMutex);
      Platform::terminate();

      ServerControl::terminate();
    }

    void update() {
      SysTime::USecond64 frameStartTime = GameTime::get();
      double timeDelta = 0.000001*(frameStartTime-frameLastTime);

      Platform::handlePreFrame();

      readNet();
      PingPong::update(timeDelta);

      updateKeyboard();
      flow.update(timeDelta, keyboard);
      Carrier::update(timeDelta);

      renderer.draw();

      Net::dispatch();

      Platform::handlePostFrame();

      ServerControl::update();

      Platform::present();
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
