#include "SysTime/SysTime.h"
#include "Common/GameTime.h"

namespace GameTime {
  uint64_t startTime;

  void initialize() {
    startTime = SysTime::get();
  }

  uint64_t get() {
    return SysTime::get()-startTime;
  }
}
