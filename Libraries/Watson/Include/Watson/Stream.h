#ifndef WATSON_STREAM_H
#define WATSON_STREAM_H

#include <stdint.h>

namespace Watson {
  class Stream {
  public:
    void write(const void *data, uint16_t length);
    void* get(uint8_t index);
    uint8_t getCount() const;
    void clear();
  private:
    static const uint8_t valueMax = 128;
    uint16_t offsets[valueMax];
    static const uint16_t capacity = 256;
    char buffer[capacity];
    uint8_t count = 0;
    uint16_t length = 0;
  };
}

#endif
