#include "Misc/FrameAllocator.h"
#include "Simulation/Event/EventStreamWriter.h"
#include "Simulation/Event/EventSystem.h"

namespace Simulation {
  namespace EventSystem {
    EventStreamWriter mainWriter;
    FrameAllocator allocator;

    void initialize() {
      mainWriter.allocator = &allocator;
    }

    void report(const void *event, uint8_t length) {
      mainWriter.write(event, length);
    }

    void clear() {
      mainWriter.clear();
      allocator.clear();
    }
  }
}
