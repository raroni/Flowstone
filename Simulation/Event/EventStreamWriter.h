#ifndef SIMULATION_EVENT_STREAM_WRITER_H
#define SIMULATION_EVENT_STREAM_WRITER_H

#include <stdint.h>
#include "Misc/FrameAllocator.h"

namespace Simulation {
  class EventStreamWriter {
  public:
    FrameAllocator *allocator = nullptr;
    void write(const void *data, uint16_t dataLength);
    const void* getStream() const;
    void clear();
    uint16_t getLength() const;
  private:
    void grow(uint16_t minimumCapacity);
    uint16_t streamLength = 0;
    uint16_t streamCapacity = 0;
    void *stream = nullptr;
  };
}

#endif
