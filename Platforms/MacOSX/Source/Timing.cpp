#include <unistd.h>
#include <sys/time.h>
#include "SysTime/SysTime.h"
#include "Quanta/Util.h"
#include "MacOSX/Config.h"
#include "MacOSX/Timing.h"

static uint64_t gameStartTime;
static double frameStartTime;
static double frameLastTime;

static double getTime() {
  uint64_t elapsed = SysTime::get()-gameStartTime;
  return elapsed*0.000001;
}

void timingInitialize() {
  gameStartTime = SysTime::get();
  auto x = getTime();
  frameLastTime = x;
}

void timingStartFrame() {
  auto x = getTime();
  frameStartTime = x;
}

void timingWaitForNextFrame() {
  auto now = getTime();
  double duration = now-frameStartTime;
  double rest = Config::targetFrameDuration-duration;
  usleep(Quanta::max(rest*1000000.0, 0.0));
  frameLastTime = frameStartTime;
}

double timingGetDelta() {
  return frameStartTime-frameLastTime;
}
