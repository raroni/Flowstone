#include "SysKey/SysKey.h"
#include "Common/MessageType.h"
#include "ClientNet.h"
#include "UserGame.h"
#include "PingPong.h"
#include "ClientCarrier.h"
#include "PresentationSync.h"
#include "ClientGame.h"

void ClientGame::initialize(uint16_t resolutionWidth, uint16_t resolutionHeight) {
  renderer.initialize();
  renderer.updateResolution({ resolutionWidth, resolutionHeight });
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
  UserGame::startServer();

  //char test[] = { static_cast<char>(MessageType::Test) };
  //ClientCarrier::send(test, 4, 30);
}

void ClientGame::update(double timeDelta) {
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
}

void ClientGame::updateKeyboard() {
  SysKey::Event event;
  while(SysKey::pollEvent(event)) {
    if(event.type == SysKey::EventType::Down) {
      keyboard.handleDown(event.key);
    } else {
      keyboard.handleUp(event.key);
    }
  }
}

void ClientGame::readNet() {
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
