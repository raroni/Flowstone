#ifndef SIMULATION_EVENT_SUBSCRIPTION_LIST_H
#define SIMULATION_EVENT_SUBSCRIPTION_LIST_H

#include "Simulation/Event/EventType.h"
#include "Simulation/Event/EventStreamWriter.h"

namespace Simulation {
  namespace EventSubscriptionList {
    void initialize(FrameAllocator *allocator);
    uint8_t create(EventType *types, uint8_t typeCount);
    EventStreamWriter* getWriter(uint8_t subscriptionID);
    uint8_t getCount();
    bool hasType(uint8_t subscriptionID, EventType type);
  }
}

#endif
