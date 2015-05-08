#ifndef CLIENT_RENDERER_FEEDER_H
#define CLIENT_RENDERER_FEEDER_H

#include "Interpolation/Handle.h"
#include "Animation/PoseIndex.h"
#include "Rendering/StaticMeshInstanceHandle.h"
#include "Rendering/BoneMeshInstanceHandle.h"

namespace Client {
  namespace RenderFeed {
    uint16_t createBoneMeshFeed(Interpolation::Handle interpolation, Animation::PoseIndex pose, Rendering::BoneMeshInstanceHandle mesh);
    void update();
  }
}

#endif
