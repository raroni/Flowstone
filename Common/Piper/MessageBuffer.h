#ifndef PIPER_MESSAGE_BUFFER_H
#define PIPER_MESSAGE_BUFFER_H

#include <stdint.h>

namespace Piper {
  class MessageBuffer {
  public:
    void write(const void *message, uint16_t messageLength);
    uint16_t read(uint16_t position, const void **message);
    void clear();
    uint16_t getCount() const;
    static const uint16_t maxCount = 128;
  private:
    uint16_t count = 0;
    uint16_t offsets[maxCount] = { 0 };
    uint16_t lengths[maxCount] = { 0 };
    static const uint16_t capacity = 20*1024;
    char storage[capacity];
  };
}

#endif
