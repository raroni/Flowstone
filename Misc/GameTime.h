#ifndef GAME_TIME_H
#define GAME_TIME_H

#include <stdint.h>
#include "SysTime/SysTime.h"

namespace GameTime {
  void initialize();
  SysTime::USecond64 get();
}

#endif
