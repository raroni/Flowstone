#include <unistd.h>
#include <sys/time.h>
#include "Common/GameTime.h"
#include "SysTime/SysTime.h"
#include "Quanta/Util.h"
#include "MacOSX/Config.h"
#include "MacOSX/Timing.h"

static uint64_t gameStartTime;
static uint64_t frameStartTime;
static uint64_t frameLastTime;

void timingInitialize() {
  gameStartTime = SysTime::get();
  frameLastTime = GameTime::get();
}

void timingStartFrame() {
  frameStartTime = GameTime::get();
}

void timingWaitForNextFrame() {
  uint64_t now = GameTime::get();
  uint64_t duration = now-frameStartTime;
  double rest = Config::targetFrameDuration-0.000001*duration;
  usleep(Quanta::max(rest*1000000.0, 0.0));
  frameLastTime = frameStartTime;
}

double timingGetDelta() {
  return 0.000001*(frameStartTime-frameLastTime);
}
