#ifndef SIMULATION_EVENT_STREAM_ITERATOR_H
#define SIMULATION_EVENT_STREAM_ITERATOR_H

#include "Simulation/Event/EventType.h"
#include "Simulation/Event/SteeringStartEvent.h"
#include "Simulation/Event/SteeringStopEvent.h"

namespace Simulation {
  class EventStreamIterator {
  public:
    bool atEnd() const;
    const void *stream;
    uint16_t length;
    const SteeringStartEvent* readSteeringStart();
    const SteeringStopEvent* readSteeringStop();
    EventType sampleType() const;
  private:
    const void* getHead() const;
    uint16_t offset = 0;
  };
}

#endif
