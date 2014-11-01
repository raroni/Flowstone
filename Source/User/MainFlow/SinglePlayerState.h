#ifndef MAIN_FLOW_SINGLE_PLAYER_H
#define MAIN_FLOW_SINGLE_PLAYER_H

#include <stddef.h>
#include <OpenGL/gl3.h>
#include "MainFlow/State.h"
#include "Animation/Animator.h"
#include "Core/Physics/Engine.h"
#include "FrameInterpolator.h"

namespace Rendering {
  class Renderer;
}

namespace MainFlow {
  class Manager;

  class SinglePlayerState : public State {
    Animation::Animator animator;
    Physics::Engine physics;
    Rendering::Renderer &renderer;
    FrameInterpolator frameInterpolator;
    int x = 0;
    bool toRun = true;
    double stepTimeBank = 0;
    uint8_t physicsTransformID;
  public:
    SinglePlayerState(Rendering::Renderer &renderer);
    void enter();
    void update(double deltaTime);
    State* checkTransition();
  };
}

#endif
