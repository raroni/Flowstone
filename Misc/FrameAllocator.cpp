#include <stdlib.h>
#include "Misc/Error.h"
#include "Misc/FrameAllocator.h"

static const size_t blockSize = 1024;

void FrameAllocator::initialize() {
  bufferCapacity = blockSize;
  buffer = malloc(bufferCapacity);
  if(buffer == NULL) {
    fatalError("Not enough memory.");
  }
}

void* FrameAllocator::alloc(size_t size) {
  size_t newBufferLength = bufferLength+size;
  if(newBufferLength > bufferCapacity) {
    grow(newBufferLength);
  }
  void *chunk = static_cast<char*>(buffer)+bufferLength;
  bufferLength = newBufferLength;
  return chunk;
}

void FrameAllocator::grow(size_t minimumCapacity) {
  size_t blockCountIncrease = minimumCapacity/blockSize+1;
  size_t capacityIncrease = blockCountIncrease*blockSize;
  size_t newCapacity = bufferCapacity + capacityIncrease;

  buffer = realloc(buffer, newCapacity);
  if(buffer == NULL) {
    fatalError("Not enough memory.");
  }
}

void FrameAllocator::terminate() {
  free(buffer);
  bufferLength = 0;
  bufferCapacity = 0;
}

void FrameAllocator::clear() {
  bufferLength = 0;
}
