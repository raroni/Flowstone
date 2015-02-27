#ifndef GAME_CLIENT_H
#define GAME_CLIENT_H

#include "Rendering/Renderer.h"
#include "MainFlow/Manager.h"

class GameClient {
public:
  void initialize(uint16_t resolutionWidth, uint16_t resolutionHeight);
  void update(double timeDelta);
private:
  Rendering::Renderer renderer;
  MainFlow::Manager flow;
};

#endif
