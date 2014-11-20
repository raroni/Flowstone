#include "Bro/Bro.h"
#include "MainFlow/Manager.h"
#include "Rendering2/Renderer.h"
#include "Config.h"
#include "Timing.h"

static bool myHack = false;

static Rendering2::Renderer renderer;
static MainFlow::Manager flow;

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
  renderer.initialize();
  flow.initialize(renderer);
  while(!broShouldTerminate()) {
    timingStartFrame();
    broPollEvents();
    double timeDelta = timingGetDelta();
    flow.update(timeDelta);
    if(!myHack) {
      //myHack = true;
      renderer.draw();
      broSwapBuffers();
    }
    timingWaitForNextFrame();
  }
  broTerminate();
}
