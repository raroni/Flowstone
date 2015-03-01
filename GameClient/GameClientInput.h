#ifndef CLIENT_PLATFORM_INPUT_H
#define CLIENT_PLATFORM_INPUT_H

#include "KeyboardInput.h"

struct GameClientInput {
  KeyboardInput keyboard;
  double timeDelta;
  void clear();
};

#endif
