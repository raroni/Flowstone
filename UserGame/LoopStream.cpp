#include <string.h>
#include "LoopStream.h"

LoopStream::LoopStream(
  uint16_t *offsets,
  uint16_t *lengths,
  uint16_t max,
  void *storage,
  uint16_t capacity
) :
offsets(offsets),
lengths(lengths),
max(max),
storage(static_cast<char*>(storage)),
capacity(capacity) {

}

uint16_t LoopStream::read(uint16_t handle, const void **message) {
  *message = storage+offsets[handle];
  return lengths[handle];
}

bool LoopStream::write(uint16_t *handle, const void *message, uint16_t length) {
  if(head == max || head+1==tail) {
    return false;
  }
  uint16_t bytesRemaing = capacity-offsets[head];
  if(bytesRemaing < length) {
    if(tail == 0 || head == 0 || offsets[tail] < length) {
      return false;
    }
    if(tail == head) {
      tail = 0;
    }
    head = 0;
  } else {
    high = head+1;
  }
  offsets[head+1] = offsets[head]+length;
  lengths[head] = length;
  memcpy(storage+offsets[head], message, length);
  *handle = head++;
  return true;
}

void LoopStream::release(uint16_t handle) {
  lengths[handle] = 0;
  while(lengths[tail] == 0) {
    tail++;
    if(tail == head) {
      return;
    }
    if(tail == high) {
      tail = 0;
      high = head+1;
    }
  }
}
