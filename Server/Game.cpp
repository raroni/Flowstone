#include "Common/MessageType.h"
#include "Server/ServerNet.h"
#include "Server/ServerGameClientSet.h"
#include "SysThread.h"
#include "ServerPingPong.h"
#include "ServerCarrier.h"
#include "Server/Game.h"

#include <stdio.h>

namespace Server {
  namespace Game {
    bool terminationRequested = false;
    SysThread::Mutex terminationMutex;

    void initialize() {
      SysThread::initMutex(&terminationMutex);
      ServerGameClientSet::initialize();
      ServerNet::initialize();

      Piper::Address address;
      address.ip[0] = 0;
      address.ip[1] = 0;
      address.ip[2] = 0;
      address.ip[3] = 0;
      address.port = 4242;
      ServerNet::listen(address);
    }

    void terminate() {
      SysThread::destroyMutex(&terminationMutex);
    }

    void requestTermination() {
      SysThread::lock(&terminationMutex);
      terminationRequested = true;
      SysThread::unlock(&terminationMutex);
    }

    bool shouldTerminate() {
      SysThread::lock(&terminationMutex);
      bool copy = terminationRequested;
      SysThread::unlock(&terminationMutex);
      return copy;
    }

    void readPipe() {
      ServerNet::poll();

      const void *message = nullptr;
      uint16_t messageLength = 0;
      ServerGameClientID id;
      MessageType type;
      while(ServerNet::readMessage(&id, &type, &message, &messageLength)) {
        switch(type) {
          case MessageType::Ping: {
            if(messageLength == 1) {
              uint8_t pingID = *static_cast<const uint8_t*>(message);
              ServerPingPong::handlePing(id, pingID);
            }
            break;
          }
          case MessageType::Pong: {
            if(messageLength == 1) {
              uint8_t pingID = *static_cast<const uint8_t*>(message);
              ServerPingPong::handlePong(id, pingID);
            }
            break;
          }
          default:
            printf("Server got something unknown.\n");
            break;
        }
      }

      ServerNet::clear();
    }

    void update(double timeDelta) {
      readPipe();

      // do game logic
      ServerPingPong::update(timeDelta);
      ServerCarrier::update(timeDelta);

      ServerNet::dispatch();
    }

    void run() {
      while(!shouldTerminate()) {
        // todo: make better timeDelta
        double timeDelta = 0.016;
        update(timeDelta);
        SysTime::sleep(timeDelta*1000000);
      }
    }
  }
}
