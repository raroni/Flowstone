#include <unistd.h>
#include <OpenGL/gl.h>
#include "../Core/Math/Math.h"
#include "Bro/Bro.h"
#include "MainFlow/Manager.h"
#include "MainFlow/SinglePlayerState.h"

// TODO: Flyt alt kode til Source eller lign. så du kan inkludere således Core/Math.h

double targetFrameRate = 1.0/60; // TODO: Flyt dette til mere fornuftigt sted

static double lastTime;
static MainFlow::Manager flow;

int main() {
  //broSetEventCallback(handleEvent);
  broInitialize();
  lastTime = broGetTime();
  while(!broShouldTerminate()) {
    double startTime = broGetTime();
    broPollEvents();

    // TODO: Move this code to general graphicsPrepare() eller lign.
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    flow.update(startTime-lastTime);
    broSwapBuffers();
    double duration = broGetTime()-startTime;
    double budgetRest = targetFrameRate-duration;
    usleep(Math::max(budgetRest*1000000.0, 0.0));
    lastTime = startTime;
  }
  broTerminate();
}
