#ifndef CLIENT_RENDER_FEED_H
#define CLIENT_RENDER_FEED_H

#include "InterpolationHandle.h"
#include "Animation/PoseHandle.h"
#include "Rendering/StaticMeshInstanceHandle.h"
#include "Rendering/BoneMeshInstanceHandle.h"
#include "Client/BoneMeshRenderFeedHandle.h"

namespace Client {
  namespace RenderFeed {
    BoneMeshRenderFeedHandle createBoneMeshFeed(InterpolationHandle interpolation, Animation::PoseHandle pose, Rendering::BoneMeshInstanceHandle mesh);
    void update();
  }
}

#endif
