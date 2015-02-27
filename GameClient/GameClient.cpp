#include "GameClient.h"

void GameClient::initialize(uint16_t resolutionWidth, uint16_t resolutionHeight) {
  renderer.initialize();
  renderer.updateResolution({ resolutionWidth, resolutionHeight });
  flow.initialize(renderer);
}

void GameClient::update(double timeDelta) {
  flow.update(timeDelta);
  renderer.draw();
}
