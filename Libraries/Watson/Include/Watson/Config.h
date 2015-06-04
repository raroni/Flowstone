#ifndef WATSON_CONFIG_H
#define WATSON_CONFIG_H

#include <stdint.h>

namespace Watson {
  namespace Config {
    const uint8_t typeMax = 32;
    const uint16_t instanceMax = 256;
    const uint8_t nodePerTypeMax = 100;
    const uint8_t structureNodeHeaderSize = 1;
    const uint16_t inputMapCapacity = 512;
    const uint8_t inputMapValueMax = 32;
    const uint8_t boardKeyMax = 32;
    const uint8_t callbacksPerNodeType = 4;
    const uint8_t responseBufferCapacity = 64;
  }
}

#endif
