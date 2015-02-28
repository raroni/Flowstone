#ifndef GAME_CLIENT_H
#define GAME_CLIENT_H

#include "ClientPlatformInput.h"
#include "Rendering/Renderer.h"
#include "Keyboard.h"
#include "MainFlow/Manager.h"

class GameClient {
public:
  void initialize(uint16_t resolutionWidth, uint16_t resolutionHeight);
  void update(const ClientPlatformInput &input);
private:
  void updateKeyboard(const KeyboardInput &input);
  Keyboard keyboard;
  Rendering::Renderer renderer;
  MainFlow::Manager flow;
};

#endif
