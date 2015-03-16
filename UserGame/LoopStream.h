#ifndef LOOP_STREAM_H

class LoopStream {
public:
  LoopStream(
    uint16_t *offsets,
    uint16_t *lengths,
    bool *existances,
    uint16_t max,
    void *buffer,
    uint16_t capacity
  );
  uint16_t read(uint16_t handle, void **message);
  uint16_t handle write(const void *message, uint16_t length);
  void release(uint16_t handle);
private:
  void *storage;
  uint16_t max;
  uint16_t tail = 0;
  uint16_t head = 0;
};

#endif
