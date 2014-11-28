#ifndef RENDERING_DRAW_CALLS_H
#define RENDERING_DRAW_CALLS_H

#include "Rendering/BoneMeshInstanceIndex.h"

namespace Rendering {
  struct BoneMeshDrawCall {
    Backend::ObjectHandle object;
    uint16_t indexCount;
    Pose pose;
    Quanta::Matrix4 transform;
  };
}

#endif
