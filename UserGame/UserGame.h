#ifndef USER_GAME_H
#define USER_GAME_H

#include "Rendering/Renderer.h"
#include "Keyboard.h"
#include "Connection.h"
#include "MainFlow/Manager.h"

class UserGame {
public:
  void initialize(uint16_t resolutionWidth, uint16_t resolutionHeight);
  void update(double timeDelta);
private:
  void updateKeyboard();
  Connection connection;
  Keyboard keyboard;
  Rendering::Renderer renderer;
  MainFlow::Manager flow;
};

#endif
