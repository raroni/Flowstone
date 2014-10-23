#include <unistd.h>
#include "Core/Math/Math.h"
#include "Bro/Bro.h"
#include "MainFlow/Manager.h"
#include "MainFlow/SinglePlayerState.h"
#include "Config.h"
#include "BaseGraphics.h"

static double lastTime;
static MainFlow::Manager flow;

int main() {
  //broSetEventCallback(handleEvent);
  broInitialize();
  lastTime = broGetTime();
  baseGraphicsInit();
  while(!broShouldTerminate()) {
    double startTime = broGetTime();
    broPollEvents();
    baseGraphicsClear();
    flow.update(startTime-lastTime);
    broSwapBuffers();
    double duration = broGetTime()-startTime;
    double budgetRest = Config::targetFrameDuration-duration;
    usleep(Math::max(budgetRest*1000000.0, 0.0));
    lastTime = startTime;
  }
  broTerminate();
}
