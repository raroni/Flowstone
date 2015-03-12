#include <unistd.h>
#include <sys/time.h>
#include "Common/GameTime.h"
#include "SysTime/SysTime.h"
#include "Quanta/Util.h"
#include "MacOSX/Config.h"
#include "MacOSX/Timing.h"

static uint64_t gameStartTime;
static double frameStartTime;
static double frameLastTime;

void timingInitialize() {
  gameStartTime = SysTime::get();
  frameLastTime = GameTime::get();
}

void timingStartFrame() {
  frameStartTime = GameTime::get();
}

void timingWaitForNextFrame() {
  auto now = GameTime::get();
  double duration = now-frameStartTime;
  double rest = Config::targetFrameDuration-duration;
  usleep(Quanta::max(rest*1000000.0, 0.0));
  frameLastTime = frameStartTime;
}

double timingGetDelta() {
  return frameStartTime-frameLastTime;
}
