#ifndef WATSON_REQUEST_H
#define WATSON_REQUEST_H

#include <stdint.h>

namespace Watson {
  struct Request {
    uint8_t boardKey;
    uint8_t dataLength;
    void *data = nullptr;
  };
}

#endif
