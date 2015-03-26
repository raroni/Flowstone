#ifndef GAME_TIME_H
#define GAME_TIME_H

#include <stdint.h>

namespace GameTime {
  typedef uint16_t MSecond16;
  typedef int16_t MSecond16S;
  typedef uint32_t MSecond32;
  typedef int32_t MSecond32S;
  typedef uint64_t MSecond64;
  typedef uint64_t USecond64;

  void initialize();
  USecond64 get();
}

#endif
