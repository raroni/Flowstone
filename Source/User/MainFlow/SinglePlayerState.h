#ifndef MAIN_FLOW_SINGLE_PLAYER_H
#define MAIN_FLOW_SINGLE_PLAYER_H

#include <stddef.h>
#include <OpenGL/gl3.h>
#include "MainFlow/State.h"
#include "Animation/Animator.h"

namespace Rendering {
  class Renderer;
  struct Input;
}

namespace MainFlow {
  class Manager;

  class SinglePlayerState : public State {
    Animation::Animator animator;
    Rendering::Renderer &renderer;
    Rendering::Input &renderingInput;
    int x = 0;
    bool toRun = true;
  public:
    SinglePlayerState(Rendering::Renderer &renderer, Rendering::Input &renderingInput);
    void enter();
    void update(double deltaTime);
    State* checkTransition();
  };
}

#endif
