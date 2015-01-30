#ifndef RENDERING_DRAW_CALLS_H
#define RENDERING_DRAW_CALLS_H

#include "Pose.h"
#include "Rendering/BoneMeshInstanceHandle.h"
#include "Rendering/Backend/ObjectHandle.h"

namespace Rendering {
  struct BoneMeshDrawCall {
    Backend::ObjectHandle object;
    uint16_t indexCount;
    Pose pose;
    Quanta::Matrix4 transform;
  };

  struct StaticMeshDrawCall {
    Backend::ObjectHandle object;
    uint16_t indexCount;
    Quanta::Matrix4 transform;
  };
}

#endif
