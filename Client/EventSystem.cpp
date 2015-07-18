#include <assert.h>
#include "Misc/FrameAllocator.h"
#include "Simulation/Event/EventStreamWriter.h"
#include "Simulation/Event/EventSystem.h"
#include "Client/EventSystem.h"

namespace Client {
  namespace EventSystem {
    const uint8_t max = 8;
    uint8_t simulationSubscriptionIDs[max];
    Simulation::EventStreamWriter writers[max];
    uint8_t count = 0;
    FrameAllocator allocator;

    void initialize() {
      for(uint8_t i=0; i<max; ++i) {
        writers[i].allocator = &allocator;
      }
    }

    uint8_t createSubscription(Simulation::EventType *types, uint8_t typeCount) {
      assert(count != max);
      Simulation::EventSystem::createSubscription(types, typeCount);
      return count++;
    }

    void copy() {
      for(uint8_t i=0; i<count; ++i) {
        uint8_t simID = simulationSubscriptionIDs[i];
        const void *stream = Simulation::EventSystem::getEventStream(simID);
        uint16_t streamLength = Simulation::EventSystem::getEventStreamLength(simID);
        writers[i].write(stream, streamLength);
      }
    }

    void clear() {
      for(uint8_t i=0; i<count; ++i) {
        writers[i].clear();
      }
      allocator.clear();
    }

    const void* getStream(uint8_t subscriptionID) {
      return writers[subscriptionID].getStream();
    }

    uint16_t getStreamLength(uint8_t subscriptionID) {
      return writers[subscriptionID].getLength();
    }
  }
}
