#include "SysTime/SysTime.h"
#include "Common/GameTime.h"

namespace GameTime {
  uint64_t startTime;

  void initialize() {
    startTime = SysTime::get();
  }

  double get() {
    uint64_t elapsed = SysTime::get()-startTime;
    return elapsed*0.000001;
  }
}
