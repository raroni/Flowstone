#include "Simulation/Event/EventListIterator.h"

namespace Simulation {
  bool EventListIterator::atEnd() {
    return eventIndex == list->getCount();
  }

  void EventListIterator::next() {
    streamOffset += list->getEventLength(eventIndex);
    eventIndex++;
  }

  const void* EventListIterator::getEvent() const {
    return static_cast<const char*>(list->getStream())+streamOffset;
  }

  uint8_t EventListIterator::getEventLength() const {
    return list->getEventLength(eventIndex);
  }
}
