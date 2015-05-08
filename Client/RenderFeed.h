#ifndef CLIENT_RENDERER_FEEDER_H
#define CLIENT_RENDERER_FEEDER_H

#include "InterpolationHandle.h"
#include "Animation/PoseIndex.h"
#include "Rendering/StaticMeshInstanceHandle.h"
#include "Rendering/BoneMeshInstanceHandle.h"

namespace Client {
  namespace RenderFeed {
    uint16_t createBoneMeshFeed(InterpolationHandle interpolation, Animation::PoseIndex pose, Rendering::BoneMeshInstanceHandle mesh);
    void update();
  }
}

#endif
