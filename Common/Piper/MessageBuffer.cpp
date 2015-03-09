#include <string.h>
#include <assert.h>
#include "Common/Piper/MessageBuffer.h"

namespace Piper {
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
    *message = storage+offsets[position];
    return lengths[position];
  }

  void MessageBuffer::clear() {
    count = 0;
  }
}
