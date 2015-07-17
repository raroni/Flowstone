#include <assert.h>
#include "Misc/FrameAllocator.h"
#include "Simulation/Event/EventSubscriptionList.h"
#include "Simulation/Event/EventList.h"
#include "Simulation/Event/EventListIterator.h"
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

    void pump() {
      uint8_t subscriptionCount = EventSubscriptionList::getCount();
      EventListIterator iterator;
      iterator.list = &mainList;

      for(; !iterator.atEnd(); iterator.next()) {
        const void *event = iterator.getEvent();
        uint8_t eventLength = iterator.getEventLength();
        EventType type = *reinterpret_cast<const EventType*>(event);
        for(uint8_t s=0; s<subscriptionCount; ++s) {
          if(EventSubscriptionList::hasType(s, type)) {
            EventSubscriptionList::addEvent(s, event, eventLength);
          }
        }
      }
      mainList.clear();
    }

    void clear() {
      assert(mainList.getCount() == 0);
      uint8_t subscriptionCount = EventSubscriptionList::getCount();
      for(uint16_t i=0; i<subscriptionCount; ++i) {
        EventSubscriptionList::clearEvents(i);
      }
      allocator.clear();
    }
  }
}
