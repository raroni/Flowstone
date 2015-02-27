#include <unistd.h>
#include <sys/time.h>
#include "Quanta/Util.h"
#include "MacOSX/Config.h"
#include "MacOSX/Timing.h"

static double gameStartTime;
static double frameStartTime;
static double frameLastTime;

static uint64_t getSystemTime() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec*1000000+tv.tv_usec);
}

static double getTime() {
  uint64_t elapsed = getSystemTime()-gameStartTime;
  return elapsed*0.000001;
}

void timingInitialize() {
  gameStartTime = getSystemTime();
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
