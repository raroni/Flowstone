#ifndef MAIN_FLOW_SINGLE_PLAYER_H
#define MAIN_FLOW_SINGLE_PLAYER_H

#include "MainFlow/State.h"

namespace MainFlow {
  class Manager;

  class SinglePlayerState : public State {
    float x = 0;
  public:
    void update(float deltaTime) {
      x += 0.1*deltaTime;
      glColor3f(1, .85, .35);
      glBegin(GL_TRIANGLES);
      {
        glVertex3f(x+ 0, 0.6, 0);
        glVertex3f(x+ -0.2, -0.3, 0);
        glVertex3f(x+.2, -.3, 0);
      }
      glEnd();
    }
    State* checkTransition() {
      return nullptr;
    }
  };
}

#endif
