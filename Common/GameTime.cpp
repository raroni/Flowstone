#include "SysTime/SysTime.h"
#include "Common/GameTime.h"

namespace GameTime {
  uint64_t startTime;

  void initialize() {
    startTime = SysTime::get();
  }

  USecond64 get() {
    return SysTime::get()-startTime;
  }
}
