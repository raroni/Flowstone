#include <unistd.h>
#include "Quanta/Util.h"
#include "Bro/Bro.h"
#include "Config.h"
#include "Timing.h"

static double startTime;
static double lastTime;

void timingInitialize() {
  lastTime = broGetTime();
}

void timingStartFrame() {
  startTime = broGetTime();
}

void timingWaitForNextFrame() {
  double duration = broGetTime()-startTime;
  double rest = Config::targetFrameDuration-duration;
  usleep(Quanta::max(rest*1000000.0, 0.0));
  lastTime = startTime;
}

double timingGetDelta() {
  return startTime-lastTime;
}
