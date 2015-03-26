#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>

namespace Platform {
  void initialize(uint16_t resolutionWidth, uint16_t resolutionHeight);
  void handlePreFrame();
  void handlePostFrame();
  void terminate();
}

#endif
