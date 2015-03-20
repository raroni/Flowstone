#ifndef GAME_TIME_H
#define GAME_TIME_H

#include <stdint.h>

namespace GameTime {
  typedef uint16_t MSecond16;
  typedef uint64_t MSecond64;

  void initialize();
  uint64_t get();
}

#endif
