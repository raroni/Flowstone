#include "GameClient.h"

void GameClient::initialize(uint16_t resolutionWidth, uint16_t resolutionHeight) {
  renderer.initialize();
  renderer.updateResolution({ resolutionWidth, resolutionHeight });
  flow.initialize(renderer);
}

void GameClient::update(const ClientPlatformInput &input) {
  updateKeyboard(input.keyboard);
  flow.update(input.timeDelta, keyboard);
  renderer.draw();
}

void GameClient::updateKeyboard(const KeyboardInput &input) {
  for(uint16_t i=0; i<input.getCount(); ++i) {
    const KeyboardEvent &event = input.read(i);
    if(event.type == KeyboardEventType::Down) {
      keyboard.handleDown(event.key);
    } else {
      keyboard.handleUp(event.key);
    }
  }
}
