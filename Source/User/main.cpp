#include "Bro/Bro.h"
#include "MainFlow/Manager.h"
#include "Rendering/Renderer.h"
#include "Rendering/Resolution.h"
#include "Config.h"
#include "Timing.h"

static Rendering::Renderer renderer;
static MainFlow::Manager flow;
static struct {
  const uint16_t width = 800;
  const uint16_t height = 600;
} resolution;

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
  broInitialize({ resolution.width, resolution.height });
  timingInitialize();
  renderer.initialize();
  renderer.updateResolution({ resolution.width, resolution.height });
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
