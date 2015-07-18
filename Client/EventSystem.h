#ifndef CLIENT_EVENT_SYSTEM_H
#define CLIENT_EVENT_SYSTEM_H

#include <stdint.h>
#include "Simulation/Event/EventType.h"

namespace Client {
  namespace EventSystem {
    void initialize();
    uint8_t createSubscription(Simulation::EventType *types, uint8_t typeCount);
    void copy();
    void clear();
    const void* getStream(uint8_t subscriptionID);
    uint16_t getStreamLength(uint8_t subscriptionID);
  }
}

#endif
