#ifndef CLIENT_GAME_H
#define CLIENT_GAME_H

#include "Rendering/Renderer.h"
#include "Keyboard.h"
#include "SysThread.h"
#include "MainFlow/Manager.h"

class ClientGame {
public:
  void initialize();
  void update(double timeDelta);
  void terminate();
  void requestTermination();
  bool shouldTerminate();
private:
  SysThread::Thread presenter;
  bool terminationRequested = false;
  SysThread::Mutex terminateMutex;
  struct {
    const uint16_t width = 800;
    const uint16_t height = 600;
  } resolution;
  void readNet();
  void updateKeyboard();
  Keyboard keyboard;
  Rendering::Renderer renderer;
  MainFlow::Manager flow;
};

#endif
