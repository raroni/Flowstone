#ifndef PIPER_CONFIG_H
#define PIPER_CONFIG_H

#include <stdint.h>

namespace Piper {
  namespace Config {
    namespace Client {
      const uint16_t outMessageCapacity = 1024*10;
      const uint16_t outMessageMax = 128;
      const uint16_t inMessageCapacity = outMessageCapacity;
      const uint16_t inMessageMax = outMessageMax;
    }
    namespace Server {
      const uint16_t clientMax = 16;
      const uint16_t inMessageCapacity = 1024*50;
      const uint16_t inMessageMax = 256;
    }
  }
}

#endif
