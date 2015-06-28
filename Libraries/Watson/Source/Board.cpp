#include <assert.h>
#include <string.h>
#include "Watson/Board.h"

namespace Watson {
  void Board::set(uint8_t key, void *value, uint16_t length) {
    assert(Config::inputMapCapacity >= bufferLength + length);
    assert(Config::inputMapValueMax > key);
    offsets[key] = bufferLength;
    memcpy(buffer+bufferLength, value, length);
    bufferLength += length;
  }

  const void* Board::get(uint8_t key) const {
    return buffer+offsets[key];
  }

  void Board::clear() {
    bufferLength = 0;
  }
}
