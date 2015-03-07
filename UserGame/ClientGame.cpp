#include "SysKey/SysKey.h"
#include "UserGame.h"
#include "ClientGame.h"

void ClientGame::initialize(uint16_t resolutionWidth, uint16_t resolutionHeight) {
  renderer.initialize();
  renderer.updateResolution({ resolutionWidth, resolutionHeight });
  flow.initialize(renderer);

  uint8_t ip[] = { 127, 0, 0, 0 };
  connection.open(ip, 4242);

  // dummy
  UserGame::startServer();
}

void ClientGame::update(double timeDelta) {
  connection.update(timeDelta);
  updateKeyboard();
  flow.update(timeDelta, keyboard);
  renderer.draw();
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
