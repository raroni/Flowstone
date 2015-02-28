#ifndef GAME_CLIENT_H
#define GAME_CLIENT_H

#include "ClientPlatformInput.h"
#include "Rendering/Renderer.h"
#include "MainFlow/Manager.h"

class GameClient {
public:
  void initialize(uint16_t resolutionWidth, uint16_t resolutionHeight);
  void update(const ClientPlatformInput &input);
private:
  Rendering::Renderer renderer;
  MainFlow::Manager flow;
};

#endif
