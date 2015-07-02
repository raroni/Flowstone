#ifndef CLIENT_DIRECTION_H
#define CLIENT_DIRECTION_H

#include "Animation/PoseHandle.h"
#include "Database/EntityHandle.h"
#include "Client/DirectionInstanceHandle.h"
#include "Client/DirectionSteeringConfig.h"
#include "Client/DirectionGroupIndex.h"

namespace Client {
  namespace Direction {
    DirectionInstanceHandle createInstance(DirectionGroupIndex group, Animation::PoseHandle poseHandle, ::Database::EntityHandle simEntityHandle);
    DirectionGroupIndex createGroup();
    void initialize();
    void addSteering(DirectionGroupIndex group, DirectionSteeringConfig config);
    void prepare();
    void update();
  }
}

#endif
