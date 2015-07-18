#ifndef SIMULATION_EVENT_LIST_ITERATOR_H
#define SIMULATION_EVENT_LIST_ITERATOR_H

#include "Simulation/Event/EventList.h"

namespace Simulation {
  class EventListIterator {
  public:
    bool atEnd();
    void next();
    const void* getEvent() const;
    uint8_t getEventLength() const;
    EventList *list = nullptr;
  private:
    uint16_t eventIndex = 0;
    uint16_t streamOffset = 0;
  };
}

#endif
