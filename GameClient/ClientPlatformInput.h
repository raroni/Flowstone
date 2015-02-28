#ifndef CLIENT_PLATFORM_INPUT_H
#define CLIENT_PLATFORM_INPUT_H

#include "KeyboardInput.h"

struct ClientPlatformInput {
  KeyboardInput keyboard;
  double timeDelta;
  void clear();
};

#endif
