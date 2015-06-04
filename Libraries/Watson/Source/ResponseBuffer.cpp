#include <assert.h>
#include <string.h>
#include "Watson/ResponseBuffer.h"

namespace Watson {
  void ResponseBuffer::set(void *data, uint16_t length) {
    assert(length <= Config::responseBufferCapacity);
    this->length = length;
    memcpy(storage, data, length);
  }
}
