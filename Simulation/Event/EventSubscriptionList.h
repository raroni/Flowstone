#ifndef SIMULATION_EVENT_SUBSCRIPTION_LIST_H
#define SIMULATION_EVENT_SUBSCRIPTION_LIST_H

#include "Simulation/Event/EventType.h"

namespace Simulation {
  namespace EventSubscriptionList {
    void initialize(FrameAllocator *allocator);
    uint8_t create(EventType *types, uint8_t typeCount);
    uint8_t getCount();
    void addEvent(uint8_t subscriptionID, const void *event, uint8_t length);
    void clearEvents(uint8_t subscriptionID);
    bool hasType(uint8_t subscriptionID, EventType type);
  }
}

#endif
