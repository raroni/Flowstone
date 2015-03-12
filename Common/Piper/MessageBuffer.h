#ifndef PIPER_MESSAGE_BUFFER_H
#define PIPER_MESSAGE_BUFFER_H

#include <stdint.h>

namespace Piper {
  class MessageBuffer {
  public:
    MessageBuffer(
      uint16_t maxCount,
      uint16_t capacity,
      uint16_t *offsets,
      uint16_t *lengths,
      void *storage
    );
    void write(const void *message, uint16_t messageLength);
    uint16_t read(uint16_t position, const void **message);
    void clear();
    uint16_t getCount() const;
  private:
    uint16_t count = 0;
    uint16_t maxCount;
    uint16_t *offsets;
    uint16_t *lengths;
    uint16_t capacity;
    char *storage;
  };
}

#endif
