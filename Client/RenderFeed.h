#ifndef CLIENT_RENDER_FEED_H
#define CLIENT_RENDER_FEED_H

#include "InterpolationHandle.h"
#include "Animation/PoseHandle.h"
#include "Rendering/StaticMeshDrawHandle.h"
#include "Rendering/BoneMeshDrawHandle.h"
#include "Client/BoneMeshRenderFeedHandle.h"

namespace Client {
  namespace RenderFeed {
    BoneMeshRenderFeedHandle createBoneMeshFeed(InterpolationHandle interpolation, Animation::PoseHandle pose, Rendering::BoneMeshDrawHandle mesh);
    void update();
  }
}

#endif
