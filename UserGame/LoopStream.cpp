#include "LoopStream.h"

LoopStream::LoopStream(
  uint16_t *offsets,
  uint16_t *lengths,
  bool *existances,
  uint16_t max,
  void *buffer,
  uint16_t capacity
) :
offsets(offsets),
lengths(lengths),
existances(existances),
max(max),
buffer(buffer),
capacity(capacity) {

}

uint16_t LoopStream::read(uint16_t handle, void **message) {

}

uint16_t LoopStream::write(const void *message, uint16_t length) {

}

void LoopStream::release(uint16_t handle) {

}
