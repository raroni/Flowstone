#ifndef MAIN_FLOW_SINGLE_PLAYER_H
#define MAIN_FLOW_SINGLE_PLAYER_H

#include <stddef.h>
#include <OpenGL/gl3.h>
#include "MainFlow/State.h"
#include "Animation/Animator.h"
#include "AirDrag.h"
#include "Core/Physics/Engine.h"
#include "FrameInterpolator.h"

namespace Rendering {
  class Renderer;
}

namespace MainFlow {
  class Manager;

  class PlayState : public State {
    Animation::Animator animator;
    Physics::Engine physics;
    Rendering::Renderer &renderer;
    FrameInterpolator frameInterpolator;
    AirDrag airDrag;
    double stepTimeBank = 0;
    Physics::DynamicBodyIndex playerBodyIndex;
  public:
    PlayState(Rendering::Renderer &renderer);
    void enter();
    void update(double deltaTime);
    State* checkTransition();
  };
}

#endif
