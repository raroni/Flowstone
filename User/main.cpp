#include <unistd.h>
#include <algorithm>
#include <stdio.h>
#include <OpenGL/gl.h>
#include <stdlib.h>
#include "Bro/Bro.h"
#include "MainFlow/Manager.h"
#include "MainFlow/SinglePlayerState.h"

uint64_t targetFrameRate = (1.0/60.0)*1000000;

void handleSigint(int signum) {
  broRequestTermination();
}

static MainFlow::Manager flowManager;
static uint64_t lastTime;

int main() {
  signal(SIGINT, handleSigint);

  auto state = new MainFlow::SinglePlayerState(flowManager);
  flowManager.changeState(state);

  //broSetEventCallback(handleEvent);
  broInitialize();
  lastTime = broGetTime();
  while(!broShouldTerminate()) {
    broPollEvents();
    uint64_t start = broGetTime();
    flowManager.update();
    flowManager.getState()->update(0.016);
    broSwapBuffers();
    uint64_t duration = broGetTime()-start;
    int budgetRest = (int)(targetFrameRate-duration);
    usleep(std::max(budgetRest, 0));
  }
  broTerminate();
}
