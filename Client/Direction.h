#ifndef CLIENT_DIRECTION_H
#define CLIENT_DIRECTION_H

#include "Animation/PoseIndex.h"
#include "Database/EntityHandle.h"
#include "Client/DirectionHandle.h"
#include "Client/DirectionGroup.h"
#include "Client/DirectionGroupHandle.h"

namespace Client {
  namespace Direction {
    DirectionHandle create(Animation::PoseIndex poseHandle, ::Database::EntityHandle simEntityHandle, DirectionGroupHandle groupHandle);
    DirectionGroupHandle createGroup(const DirectionGroup *group);
    void prepare();
    void update();
  }
}

#endif
