#include "GameClient.h"

#include <stdio.h>

void GameClient::initialize(uint16_t resolutionWidth, uint16_t resolutionHeight) {
  renderer.initialize();
  renderer.updateResolution({ resolutionWidth, resolutionHeight });
  flow.initialize(renderer);
}

void GameClient::update(const ClientPlatformInput &input) {
  for(uint16_t i=0; i<input.keyboard.getCount(); ++i) {
    printf("Key down: %d\n", input.keyboard.read(i).key);
  }

  flow.update(input.timeDelta);
  renderer.draw();
}
