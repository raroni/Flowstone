#include <unistd.h>
#include <sys/time.h>
#include "Common/GameTime.h"
#include "SysTime/SysTime.h"
#include "Quanta/Util.h"
#include "MacOSX/Config.h"
#include "MacOSX/Timing.h"

static GameTime::USecond64 gameStartTime;
static GameTime::USecond64 frameStartTime;
static GameTime::USecond64 frameLastTime;

void timingInitialize() {
  gameStartTime = SysTime::get();
  frameLastTime = GameTime::get();
}

void timingStartFrame() {
  frameStartTime = GameTime::get();
}

void timingWaitForNextFrame() {
  GameTime::USecond64 now = GameTime::get();
  GameTime::USecond64 duration = now-frameStartTime;
  double rest = Config::targetFrameDuration-0.000001*duration;
  usleep(Quanta::max(rest*1000000.0, 0.0));
  frameLastTime = frameStartTime;
}

double timingGetDelta() {
  return 0.000001*(frameStartTime-frameLastTime);
}
