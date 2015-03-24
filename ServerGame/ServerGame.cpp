#include "Common/MessageType.h"
#include "ServerGame/ServerNet.h"
#include "ServerGame/ServerGameClientSet.h"
#include "ServerPingPong.h"
#include "ServerCarrier.h"
#include "ServerGame.h"

#include <stdio.h>

void ServerGame::initialize() {
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

void ServerGame::update(double timeDelta) {
  readPipe();

  // do game logic
  ServerPingPong::update(timeDelta);
  ServerCarrier::update(timeDelta);

  ServerNet::dispatch();
}

void ServerGame::readPipe() {
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
