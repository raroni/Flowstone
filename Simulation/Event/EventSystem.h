#ifndef SIMULATION_EVENT_SYSTEM_H
#define SIMULATION_EVENT_SYSTEM_H

#include <stdint.h>
#include "Simulation/Event/EventType.h"

namespace Simulation {
  namespace EventSystem {
    void initialize();
    void report(const void *event, uint8_t length);
    void clear();
    void pump();
    uint8_t createSubscription(EventType *types, uint8_t typeCount);
    const void* getEventStream(uint8_t subscriptionID);
    uint16_t getEventStreamLength(uint8_t subscriptionID);
  }
}

#endif
