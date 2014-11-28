#include "Bro/Bro.h"
#include "MainFlow/Manager.h"
#include "Rendering/Renderer.h"
#include "Config.h"
#include "Timing.h"

static Rendering::Renderer renderer;
static MainFlow::Manager flow;

static void updateResolution() {
  BroResolution resolution = broGetResolution();
  renderer.updateResolution(resolution.width, resolution.height);
}

void handleKeyDown(BroKey key) {
  if(key == BroKeyA) {

  }
}

void handleKeyUp(BroKey key) {
  if(key == BroKeyA) {

  }
}

int main() {
  broSetKeyDownCallback(handleKeyDown);
  broSetKeyUpCallback(handleKeyUp);
  //broSetEventCallback(handleEvent);
  broInitialize();
  timingInitialize();
  updateResolution();
  renderer.initialize();
  flow.initialize(renderer);
  while(!broShouldTerminate()) {
    timingStartFrame();
    broPollEvents();
    double timeDelta = timingGetDelta();
    flow.update(timeDelta);
    renderer.draw();
    broSwapBuffers();
    timingWaitForNextFrame();
  }
  broTerminate();
}
