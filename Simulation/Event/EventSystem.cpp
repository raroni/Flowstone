#include "Misc/FrameAllocator.h"
#include "Simulation/Event/EventSubscriptionList.h"
#include "Simulation/Event/EventStreamWriter.h"
#include "Simulation/Event/EventSystem.h"

namespace Simulation {
  namespace EventSystem {
    EventStreamWriter mainWriter;
    FrameAllocator allocator;

    void initialize() {
      mainWriter.allocator = &allocator;
      EventSubscriptionList::initialize(&allocator);
    }

    void report(const void *event, uint8_t length) {
      mainWriter.write(event, length);
    }

    uint8_t createSubscription(EventType *types, uint8_t typeCount) {
      return EventSubscriptionList::create(types, typeCount);
    }

    void clear() {
      mainWriter.clear();
      allocator.clear();
    }
  }
}
