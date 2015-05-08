#ifndef CLIENT_DIRECTION_H
#define CLIENT_DIRECTION_H

#include "Animation/PoseHandle.h"
#include "Database/EntityHandle.h"
#include "Client/DirectionHandle.h"
#include "Client/DirectionGroup.h"
#include "Client/DirectionGroupHandle.h"

namespace Client {
  namespace Direction {
    DirectionHandle create(Animation::PoseHandle poseHandle, ::Database::EntityHandle simEntityHandle, DirectionGroupHandle groupHandle);
    DirectionGroupHandle createGroup(const DirectionGroup *group);
    void prepare();
    void update();
  }
}

#endif
