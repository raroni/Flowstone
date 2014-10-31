#include "Bro/Bro.h"
#include "MainFlow/Manager.h"
#include "Rendering/Renderer.h"
#include "Rendering/Input.h"
#include "Config.h"
#include "Timing.h"

static Rendering::Input renderingInput;
static Rendering::Renderer renderer;
static MainFlow::Manager flow;

int main() {
  //broSetEventCallback(handleEvent);
  broInitialize();
  timingInitialize();
  renderer.initialize();
  flow.initialize(renderer, renderingInput);
  while(!broShouldTerminate()) {
    timingStartFrame();
    broPollEvents();
    double timeDelta = timingGetDelta();
    flow.update(timeDelta);
    renderer.draw(renderingInput);
    broSwapBuffers();
    timingWaitForNextFrame();
  }
  broTerminate();
}
