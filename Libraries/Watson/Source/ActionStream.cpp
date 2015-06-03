#include <string.h>
#include <assert.h>
#include "Watson/ActionStream.h"

namespace Watson {
  void ActionStream::write(void *data, uint16_t length) {
    offsets[count] = length;
    memcpy(buffer+length, data, length);
    this->length += length;
    count++;
  }

  void* ActionStream::get(uint8_t index) {
    assert(count > index);
    return buffer + offsets[index];
  }

  uint8_t ActionStream::getCount() const {
    return count;
  }

  void ActionStream::reset() {
    length = 0;
  }
}
