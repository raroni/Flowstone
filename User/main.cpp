#include <unistd.h>
#include <algorithm>
#include <stdio.h>
#include <OpenGL/gl.h>
#include <stdlib.h>
#include "Bro/Bro.h"
#include "MainFlow/Manager.h"
#include "MainFlow/SinglePlayerState.h"

uint64_t targetFrameRate = (1.0/60.0)*1000000; // TODO: Flyt dette til mere fornuftigt sted

// TODO: flyt denne til "bro" hvis user OGSÅ kan lave signal()
void handleSigint(int signum) {
  broRequestTermination();
}

static MainFlow::Manager flowManager;
static uint64_t lastTime;
static MainFlow::Manager flow;

int main() {
  signal(SIGINT, handleSigint);
  //broSetEventCallback(handleEvent);
  broInitialize();
  lastTime = broGetTime();
  while(!broShouldTerminate()) {
    broPollEvents();
    uint64_t start = broGetTime();

    // TODO: Move this code to general graphicsPrepare() eller lign.
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    flow.update(0.016); // TODO: do proper timeDelta calc
    broSwapBuffers();
    uint64_t duration = broGetTime()-start;
    int budgetRest = (int)(targetFrameRate-duration);
    usleep(std::max(budgetRest, 0));
  }
  broTerminate();
}
