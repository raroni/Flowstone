#include "SysTime/SysTime.h"
#include "Common/GameTime.h"

namespace GameTime {
  SysTime::USecond64 startTime;

  void initialize() {
    startTime = SysTime::get();
  }

  SysTime::USecond64 get() {
    return SysTime::get()-startTime;
  }
}
