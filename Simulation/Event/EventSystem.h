#ifndef SIMULATION_EVENT_SYSTEM_H
#define SIMULATION_EVENT_SYSTEM_H

#include <stdint.h>

namespace Simulation {
  namespace EventSystem {
    void report(const void *event, uint8_t length);
    void clear();
    void pump();
  }
}

#endif
