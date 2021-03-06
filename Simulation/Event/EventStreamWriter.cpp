#include <string.h>
#include "Simulation/Event/EventStreamWriter.h"

namespace Simulation {
  void EventStreamWriter::write(const void *data, uint16_t dataLength) {
    uint16_t newStreamLength = streamLength+dataLength;
    if(newStreamLength > streamCapacity) {
      grow(newStreamLength);
    }
    char *target = static_cast<char*>(stream)+streamLength;
    memcpy(target, data, dataLength);
    streamLength = newStreamLength;
  }

  const void* EventStreamWriter::getStream() const {
    return stream;
  }

  uint16_t EventStreamWriter::getLength() const {
    return streamLength;
  }

  void EventStreamWriter::clear() {
    if(streamCapacity != 0) {
      allocator->free(stream);
      streamCapacity = 0;
      streamLength = 0;
    }
  }

  void EventStreamWriter::grow(uint16_t minimumCapacity) {
    static uint16_t blockSize = 1024;
    uint16_t minimumCapacityIncrease = minimumCapacity-streamCapacity;
    uint16_t blockIncreaseCount = minimumCapacityIncrease/blockSize+1;
    uint16_t capacityIncrease = blockIncreaseCount*blockSize;
    uint16_t newCapacity = streamCapacity+capacityIncrease;
    uint16_t oldCapacity = streamCapacity;

    void *oldStream = stream;
    void *newStream = allocator->alloc(newCapacity);

    if(oldCapacity != 0) {
      memcpy(newStream, oldStream, oldCapacity);
      allocator->free(oldStream);
    }

    stream = newStream;
    streamCapacity = newCapacity;
  }
}
