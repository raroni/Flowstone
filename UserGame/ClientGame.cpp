#include "SysKey/SysKey.h"
#include "Common/MessageType.h"
#include "ClientNet.h"
#include "UserGame.h"
#include "PingPong.h"
#include "ClientCarrier.h"
#include "ClientGame.h"

#include <stdio.h>

void ClientGame::initialize(uint16_t resolutionWidth, uint16_t resolutionHeight) {
  renderer.initialize();
  renderer.updateResolution({ resolutionWidth, resolutionHeight });
  flow.initialize(renderer);

  Piper::Address address;
  address.ip[0] = 127;
  address.ip[1] = 0;
  address.ip[2] = 0;
  address.ip[3] = 1;
  address.port = 4242;
  ClientNet::setAddress(address);

  // dummy
  UserGame::startServer();

  char test[] = "hey";
  ClientCarrier::send(test, 4, 30);
}

void ClientGame::update(double timeDelta) {
  readNet();
  PingPong::update(timeDelta);

  updateKeyboard();
  flow.update(timeDelta, keyboard);
  ClientCarrier::update(timeDelta);

  renderer.draw();
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

  const void *message = nullptr;
  uint16_t messageLength = 0;

  while(ClientNet::readMessage(&message, &messageLength)) {
    MessageType type = *static_cast<const MessageType*>(message);
    switch(type) {
      case MessageType::Pong:
        if(messageLength == 2) {
          uint8_t pingID = static_cast<const uint8_t*>(message)[1];
          PingPong::handlePong(pingID);
        }
        break;
      default:
        printf("Client got something unknown.");
        break;
    }
  }
  ClientNet::clear();
}
