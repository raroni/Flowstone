#include "SysKey/SysKey.h"
#include "UserGame.h"
#include "PingPong.h"
#include "ClientGame.h"

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
  pipe.setAddress(address);

  PingPong::setPipe(pipe);

  // dummy
  UserGame::startServer();
}

void ClientGame::update(double timeDelta) {
  readPipe();
  PingPong::update(timeDelta);

  updateKeyboard();
  flow.update(timeDelta, keyboard);

  renderer.draw();
  pipe.dispatch();
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

void ClientGame::readPipe() {
  pipe.poll();

  const void *message = nullptr;
  uint16_t messageLength = 0;

  while(pipe.readMessage(&message, &messageLength)) {

  }
  pipe.clear();
}
