#ifndef CLIENT_DIRECTION_H
#define CLIENT_DIRECTION_H

#include "Animation/PoseHandle.h"
#include "Database/EntityHandle.h"
#include "Client/DirectionInstanceHandle.h"
#include "Client/DirectionGroupIndex.h"

namespace Client {
  namespace Direction {
    DirectionInstanceHandle createInstance(DirectionGroupIndex group, Animation::PoseHandle poseHandle, ::Database::EntityHandle simEntityHandle);
    DirectionGroupIndex createGroup(uint8_t instanceMax);
    void initialize();
    void attachSteeringStyle(DirectionGroupIndex group, uint8_t idleAnimation, uint8_t movingAnimation);
    void prepare();
    void update();
  }
}

#endif
