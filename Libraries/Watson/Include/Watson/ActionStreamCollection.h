#ifndef WATSON_ACTION_STREAM_COLLECTION_H
#define WATSON_ACTION_STREAM_COLLECTION_H

#include "Watson/Stream.h"

namespace Watson {
  namespace ActionStreamCollection {
    void createList(TypeIndex typeIndex);
    Stream* get(TypeIndex typeIndex, uint16_t instanceIndex);
    void move(TypeIndex typeIndex, uint16_t sourceIndex, uint16_t destinationIndex);
  }
}

#endif
