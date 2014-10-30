#include "Bro/Bro.h"
#include "MainFlow/Manager.h"
#include "Animation/Animator.h"
#include "Rendering/Renderer.h"
#include "Config.h"
#include "Timing.h"

static Rendering::Renderer renderer;
static Animation::Animator animator;
static MainFlow::Manager flow;

int main() {
  //broSetEventCallback(handleEvent);
  broInitialize();
  timingInitialize();
  renderer.initialize();
  flow.initialize(animator, renderer);
  while(!broShouldTerminate()) {
    timingStartFrame();
    broPollEvents();
    double timeDelta = timingGetDelta();
    flow.update(timeDelta);
    animator.update(timeDelta);
    renderer.draw(animator.getWorldPoses());
    broSwapBuffers();
    timingWaitForNextFrame();
  }
  broTerminate();
}
