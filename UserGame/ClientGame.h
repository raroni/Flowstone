#ifndef CLIENT_GAME_H
#define CLIENT_GAME_H

#include "Rendering/Renderer.h"
#include "Keyboard.h"
#include "ClientConnection.h"
#include "MainFlow/Manager.h"

class ClientGame {
public:
  void initialize(uint16_t resolutionWidth, uint16_t resolutionHeight);
  void update(double timeDelta);
private:
  void updateKeyboard();
  ClientConnection connection;
  Keyboard keyboard;
  Rendering::Renderer renderer;
  MainFlow::Manager flow;
};

#endif
