#ifndef CLIENT_DIRECTION_EVENT_LIST_H
#define CLIENT_DIRECTION_EVENT_LIST_H

#include "Client/DirectionEvent.h"

namespace Client {
  namespace DirectionEventList {
    void add(const DirectionEvent *event);
    const DirectionEvent* get(uint16_t index);
    uint16_t getCount();
    void clear();
  }
}

#endif
