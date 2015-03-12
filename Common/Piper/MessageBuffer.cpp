#include <string.h>
#include <assert.h>
#include "Common/Piper/MessageBuffer.h"

namespace Piper {
  MessageBuffer::MessageBuffer(
    uint16_t maxCount,
    uint16_t capacity,
    uint16_t *offsets,
    uint16_t *lengths,
    void *storage
  ) {
    this->maxCount = maxCount;
    this->capacity = capacity;
    this->offsets = offsets;
    this->lengths = lengths;
    this->storage = static_cast<char*>(storage);
  }

  void MessageBuffer::write(const void *message, uint16_t messageLength) {
    assert(count != maxCount);
    uint16_t offset = offsets[count];
    memcpy(storage+offset, message, messageLength);
    offsets[count+1] = offset+messageLength;
    lengths[count] = messageLength;
    count++;
  }

  uint16_t MessageBuffer::getCount() const {
    return count;
  }

  uint16_t MessageBuffer::read(uint16_t position, const void **message) {
    assert(position < maxCount);
    if(position >= count) {
      return 0;
    } else {
      *message = storage+offsets[position];
      return lengths[position];
    }
  }

  void MessageBuffer::clear() {
    count = 0;
  }
}
