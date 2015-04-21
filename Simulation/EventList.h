#ifndef SIMULATION_EVENT_LIST_H
#define SIMULATION_EVENT_LIST_H

#include <stdint.h>

namespace Simulation {
  class EventList {
  public:
    uint16_t getCount() const;
    void clear();
  private:
    uint16_t count = 0;
  };
}

#endif
