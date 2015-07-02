#ifndef CLIENT_DIRECTION_EVENT_H
#define CLIENT_DIRECTION_EVENT_H

#include "Database/EntityHandle.h"
#include "Client/Direction/DirectionEventType.h"

namespace Client {
  struct DirectionEvent {
    DirectionEventType type;
    Database::EntityHandle entity;
  };
}

#endif
