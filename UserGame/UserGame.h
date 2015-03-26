#ifndef USER_GAME_H
#define USER_GAME_H

#include <stdint.h>

namespace UserGame {
  void initialize(uint16_t resolutionWidth, uint16_t resolutionHeight);
  void update();
  void startServer();
}

#endif
