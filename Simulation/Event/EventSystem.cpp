#include "Misc/FrameAllocator.h"
#include "Simulation/Event/EventSubscriptionList.h"
#include "Simulation/Event/EventList.h"
#include "Simulation/Event/EventSystem.h"

namespace Simulation {
  namespace EventSystem {
    EventList mainList;
    FrameAllocator allocator;

    void initialize() {
      mainList.setAllocator(&allocator);
      EventSubscriptionList::initialize(&allocator);
    }

    void report(const void *event, uint8_t length) {
      mainList.add(event, length);
    }

    uint8_t createSubscription(EventType *types, uint8_t typeCount) {
      return EventSubscriptionList::create(types, typeCount);
    }

    void clear() {
      mainList.clear();
      allocator.clear();
    }
  }
}
