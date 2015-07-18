#ifndef CLIENT_DIRECTION_H
#define CLIENT_DIRECTION_H

#include "Animation/PoseHandle.h"
#include "Database/EntityHandle.h"
#include "Client/Direction/DirectionInstanceHandle.h"
#include "Client/Direction/DirectionSteeringConfig.h"
#include "Client/Direction/DirectionHarvestingConfig.h"
#include "Client/Direction/DirectionGroupIndex.h"

namespace Client {
  namespace Direction {
    DirectionInstanceHandle createInstance(DirectionGroupIndex group, Animation::PoseHandle poseHandle, ::Database::EntityHandle simEntityHandle);
    DirectionGroupIndex createGroup();
    void initialize();
    void addSteering(DirectionGroupIndex group, DirectionSteeringConfig config);
    void addHarvesting(DirectionGroupIndex group, DirectionHarvestingConfig config);
    void prepare();
    void update();
  }
}

#endif
