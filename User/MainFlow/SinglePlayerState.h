#include "MainFlow/State.h"

namespace MainFlow {
  class Manager;

  class SinglePlayerState : public State {
    float x = 0;
  public:
    SinglePlayerState(Manager &manager) : State(manager) { }
    void update(float deltaTime) {
      glClearColor(1, 0, 0, 1);
      glClear(GL_COLOR_BUFFER_BIT);

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
  };
}
