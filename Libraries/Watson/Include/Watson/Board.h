#ifndef WATSON_BOARD_H
#define WATSON_BOARD_H

#include "Watson/Config.h"

namespace Watson {
  class Board {
  public:
    void* get(uint8_t key);
    void set(uint8_t key, void *value, uint16_t length);
    void clear();
  private:
    char buffer[Config::inputMapCapacity];
    uint16_t offsets[Config::inputMapValueMax];
    uint16_t bufferLength = 0;
  };
}

#endif
