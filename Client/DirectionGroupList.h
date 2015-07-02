#ifndef CLIENT_DIRECTION_GROUP_LIST_H
#define CLIENT_DIRECTION_GROUP_LIST_H

#include "Database/EntityHandle.h"
#include "Animation/PoseHandle.h"
#include "Client/DirectionGroupIndex.h"

namespace Client {
  namespace DirectionGroupList {
    DirectionGroupIndex create(uint8_t instanceMax);
    void addInstance(DirectionGroupIndex group, Animation::PoseHandle pose, Database::EntityHandle simEntity);
  }
}

#endif
