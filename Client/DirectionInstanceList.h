#ifndef CLIENT_DIRECTION_INSTANCE_LIST_H
#define CLIENT_DIRECTION_INSTANCE_LIST_H

#include "Client/DirectionGroupIndex.h"
#include "Client/DirectionInstanceHandle.h"

namespace Client {
  namespace DirectionInstanceList {
    DirectionInstanceHandle create(DirectionGroupIndex group);
  }
}

#endif
