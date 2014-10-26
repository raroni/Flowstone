#ifndef MAIN_FLOW_SINGLE_PLAYER_H
#define MAIN_FLOW_SINGLE_PLAYER_H

#include <stddef.h>
#include <OpenGL/gl3.h>
#include "MainFlow/State.h"

namespace Rendering {
  class Renderer;
}

namespace MainFlow {
  class Manager;

  class SinglePlayerState : public State {
    Rendering::Renderer &renderer;
  public:
    SinglePlayerState(Rendering::Renderer &renderer);
    void enter();
    void update(double deltaTime);
    State* checkTransition();
  };
}

#endif
