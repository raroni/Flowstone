#include <assert.h>
#include "Conrad/BitSet128.h"
#include "Simulation/Event/EventConfig.h"
#include "Simulation/Event/EventSubscriptionList.h"

namespace Simulation {
  namespace EventSubscriptionList {
    const uint8_t max = EventConfig::subscriptionMax;
    static_assert(static_cast<uint16_t>(EventType::Count) <= 128, "EventSubscriptionList can only handle 128 event types due to use of BitSet128.");
    BitSet128 typeSets[max];
    EventStreamWriter writers[max];
    uint8_t count = 0;

    void initialize(FrameAllocator *allocator) {
      for(uint8_t i=0; i<max; ++i) {
        writers[i].allocator = allocator;
      }
    }

    uint8_t create(EventType *types, uint8_t typeCount) {
      assert(count != max);
      BitSet128 *set = &typeSets[count];
      for(uint8_t i=0; i<typeCount; ++i) {
        set->set(static_cast<uint8_t>(types[i]));
      }
      count++;
    }

    EventStreamWriter* getWriter(uint8_t subscriptionID) {
      return &writers[subscriptionID];
    }

    uint8_t getCount() {
      return count;
    }

    bool hasType(uint8_t subscriptionID, EventType type) {
      return typeSets[subscriptionID].get(static_cast<uint8_t>(type));
    }
  }
}
