#ifndef LOOP_STREAM_H

#include <stdint.h>

class LoopStream {
public:
  LoopStream(
    uint16_t *offsets,
    uint16_t *lengths,
    uint16_t max,
    void *storage,
    uint16_t capacity
  );
  uint16_t read(uint16_t handle, const void **message);
  bool write(uint16_t *handle, const void *message, uint16_t length);
  void release(uint16_t handle);
private:
  uint16_t *offsets;
  uint16_t *lengths;
  uint16_t max;
  char *storage;
  uint16_t capacity;
  uint16_t high = 0;
  uint16_t tail = 0;
  uint16_t head = 0;
};

#endif
