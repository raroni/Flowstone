#include <string.h>
#include <assert.h>
#include "Watson/Stream.h"

namespace Watson {
  void Stream::write(const void *data, uint16_t length) {
    offsets[count] = this->length;
    memcpy(buffer+this->length, data, length);
    this->length += length;
    count++;
  }

  void* Stream::get(uint8_t index) {
    assert(count > index);
    return buffer + offsets[index];
  }

  uint8_t Stream::getCount() const {
    return count;
  }

  void Stream::clear() {
    count = 0;
    length = 0;
  }
}
