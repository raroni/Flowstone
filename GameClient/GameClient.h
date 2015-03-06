#ifndef GAME_CLIENT_H
#define GAME_CLIENT_H

#include "GameClientInput.h"
#include "Rendering/Renderer.h"
#include "Keyboard.h"
#include "Connection.h"
#include "MainFlow/Manager.h"

class GameClient {
public:
  void initialize(uint16_t resolutionWidth, uint16_t resolutionHeight);
  void update(const GameClientInput &input);
private:
  void updateKeyboard(const KeyboardInput &input);
  Connection connection;
  Keyboard keyboard;
  Rendering::Renderer renderer;
  MainFlow::Manager flow;
};

#endif
