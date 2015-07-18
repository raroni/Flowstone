#ifndef FRAME_ALLOCATOR_H
#define FRAME_ALLOCATOR_H

#include <stddef.h>

class FrameAllocator {
public:
  void initialize();
  void* alloc(size_t size);
  void clear();
  void terminate();
  void free(void *chunk);
private:
  void grow(size_t minimumCapacity);
  void *buffer = nullptr;
  size_t bufferLength = 0;
  size_t bufferCapacity = 0;
};

#endif
