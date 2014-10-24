#include "Bro/Bro.h"
#include "MainFlow/Manager.h"
#include "MainFlow/SinglePlayerState.h"
#include "Config.h"
#include "ShaderLoading.h"
#include "BaseGraphics.h"
#include "Timing.h"

static MainFlow::Manager flow;
ShaderRegistry shaderRegistry;

int main() {
  //broSetEventCallback(handleEvent);
  broInitialize();
  timingInitialize();
  loadShaders(shaderRegistry);
  baseGraphicsInit();
  while(!broShouldTerminate()) {
    timingStartFrame();
    broPollEvents();
    baseGraphicsClear();
    flow.update(timingGetDelta());
    broSwapBuffers();
    timingWaitForNextFrame();
  }
  broTerminate();
}
