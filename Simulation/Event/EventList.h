#ifndef SIMULATION_EVENT_LIST_H
#define SIMULATION_EVENT_LIST_H

#include "Simulation/Event/EventStreamWriter.h"

namespace Simulation {
  class EventList {
  public:
    void setAllocator(FrameAllocator *allocator);
    void add(const void *event, uint8_t eventLength);
    void clear();
    uint16_t getCount() const;
    uint8_t getEventLength(uint16_t index);
    const void* getStream() const;
  private:
    void grow();
    FrameAllocator *allocator = nullptr;
    uint16_t count = 0;
    uint16_t max = 0;
    uint8_t *lengths = nullptr;
    EventStreamWriter streamWriter;
  };
}

#endif
