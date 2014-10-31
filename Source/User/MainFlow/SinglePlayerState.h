#ifndef MAIN_FLOW_SINGLE_PLAYER_H
#define MAIN_FLOW_SINGLE_PLAYER_H

#include <stddef.h>
#include <OpenGL/gl3.h>
#include "MainFlow/State.h"

namespace Rendering {
  class Renderer;
}

namespace Animation {
  class Animator;
}

namespace MainFlow {
  class Manager;

  class SinglePlayerState : public State {
    Animation::Animator &animator;
    Rendering::Renderer &renderer;
    int x = 0;
    bool toRun = true;
  public:
    SinglePlayerState(Animation::Animator &animator, Rendering::Renderer &renderer);
    void enter();
    void update(double deltaTime);
    State* checkTransition();
  };
}

#endif
