#ifndef CLIENT_GAME_H
#define CLIENT_GAME_H

#include "Common/Piper/Client.h"
#include "Rendering/Renderer.h"
#include "Keyboard.h"
#include "MainFlow/Manager.h"

class ClientGame {
public:
  void initialize(uint16_t resolutionWidth, uint16_t resolutionHeight);
  void update(double timeDelta);
private:
  void readPipe();
  void updateKeyboard();
  Piper::Client pipe;
  Keyboard keyboard;
  Rendering::Renderer renderer;
  MainFlow::Manager flow;
};

#endif
