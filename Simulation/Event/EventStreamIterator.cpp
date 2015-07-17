#include <assert.h>
#include "Simulation/Event/EventStreamIterator.h"

namespace Simulation {
  const void* EventStreamIterator::getHead() const {
    const char* byteStream = static_cast<const char*>(stream);
    return byteStream+offset;
  }

  bool EventStreamIterator::atEnd() const {
    assert(offset <= length);
    return length == offset;
  }

  EventType EventStreamIterator::sampleType() const {
    const EventType* type = static_cast<const EventType*>(getHead());
    return *type;
  }

  const SteeringStartEvent* EventStreamIterator::readSteeringStart() {
    const SteeringStartEvent* event = static_cast<const SteeringStartEvent*>(getHead());
    offset += sizeof(SteeringStartEvent);
    return event;
  }

  const SteeringStopEvent* EventStreamIterator::readSteeringStop() {
    const SteeringStopEvent* event = static_cast<const SteeringStopEvent*>(getHead());
    offset += sizeof(SteeringStopEvent);
    return event;
  }
}
