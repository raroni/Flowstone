#include <string.h>
#include "Simulation/Event/EventList.h"

namespace Simulation {
  void EventList::setAllocator(FrameAllocator *allocator) {
    this->allocator = allocator;
    streamWriter.allocator = allocator;
  }

  void EventList::add(const void *event, uint8_t length) {
    if(count == max) {
      grow();
    }
    lengths[count] = length;
    streamWriter.write(event, length);
    count++;
  }

  void EventList::grow() {
    uint16_t oldMax = max;
    uint16_t newMax = oldMax+100;

    uint16_t oldCapacity = oldMax*sizeof(uint8_t);
    uint16_t newCapacity = newMax*sizeof(uint8_t);

    uint8_t *oldLengths = lengths;
    uint8_t *newLengths = static_cast<uint8_t*>(allocator->alloc(newCapacity));

    if(oldCapacity != 0) {
      memcpy(newLengths, oldLengths, oldCapacity);
      allocator->free(oldLengths);
    }

    lengths = newLengths;
    max = newMax;
  }

  void EventList::clear() {
    if(count != 0) {
      allocator->free(lengths);
      lengths = nullptr;
      count = 0;
      max = 0;
      streamWriter.clear();
    }
  }
}
