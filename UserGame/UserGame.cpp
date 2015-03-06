#include "UserGame.h"

void UserGame::initialize(uint16_t resolutionWidth, uint16_t resolutionHeight) {
  renderer.initialize();
  renderer.updateResolution({ resolutionWidth, resolutionHeight });
  flow.initialize(renderer);

  uint8_t ip[] = { 127, 0, 0, 0 };
  connection.open(ip, 4242);
}

void UserGame::update(double timeDelta) {
  updateKeyboard();
  flow.update(timeDelta, keyboard);
  renderer.draw();
}

void UserGame::updateKeyboard() {
  /*
  temporarily disabled until we have SysKey#poll or something

  for(uint16_t i=0; i<input.getCount(); ++i) {
    const KeyboardEvent &event = input.read(i);
    if(event.type == KeyboardEventType::Down) {
      keyboard.handleDown(event.key);
    } else {
      keyboard.handleUp(event.key);
    }
  }
  */
}
