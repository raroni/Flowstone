#ifndef CLIENT_DIRECTION_INSTANCE_LIST_H
#define CLIENT_DIRECTION_INSTANCE_LIST_H

#include "Database/EntityHandle.h"
#include "Animation/PoseHandle.h"
#include "Client/DirectionGroupIndex.h"
#include "Client/DirectionInstanceHandle.h"

namespace Client {
  namespace DirectionInstanceList {
    DirectionInstanceHandle create(DirectionGroupIndex group, Animation::PoseHandle pose, Database::EntityHandle simEntity);
    DirectionGroupIndex getGroup(uint16_t index);
    Animation::PoseHandle getPoseHandle(uint16_t index);
    uint16_t getIndexByEntity(Database::EntityHandle handle);
  }
}

#endif
