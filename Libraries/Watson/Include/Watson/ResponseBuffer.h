#ifndef WATSON_RESPONSE_BUFFER_H
#define WATSON_RESPONSE_BUFFER_H

#include "Watson/Config.h"

namespace Watson {
  struct ResponseBuffer {
    void set(void *data, uint16_t length);
    char storage[Config::responseBufferCapacity];
    uint16_t length = 0;
  };
}

#endif
