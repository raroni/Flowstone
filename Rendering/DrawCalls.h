#ifndef RENDERING_DRAW_CALLS_H
#define RENDERING_DRAW_CALLS_H

#include "Animation/Pose.h"
#include "Rendering/BoneMeshDrawHandle.h"
#include "SysGFX/ObjectHandle.h"

namespace Rendering {
  struct BoneMeshDrawCall {
    SysGFX::ObjectHandle object;
    uint16_t indexCount;
    Animation::Pose pose;
    Quanta::Matrix4 transform;
  };

  struct StaticMeshDrawCall {
    SysGFX::ObjectHandle object;
    uint16_t indexCount;
    Quanta::Matrix4 transform;
  };
}

#endif
