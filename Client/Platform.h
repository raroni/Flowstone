#ifndef CLIENT_PLATFORM_H
#define CLIENT_PLATFORM_H

#include <stdint.h>

namespace Client {
  namespace Platform {
    void initialize(uint16_t resolutionWidth, uint16_t resolutionHeight);
    void handlePreFrame();
    void handlePostFrame();
    void terminate();
    void present();
  }
}

#endif
