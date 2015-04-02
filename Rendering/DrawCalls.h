#ifndef RENDERING_DRAW_CALLS_H
#define RENDERING_DRAW_CALLS_H

#include "Client/Pose.h"
#include "Rendering/BoneMeshInstanceHandle.h"
#include "SysGFX/ObjectHandle.h"

namespace Rendering {
  struct BoneMeshDrawCall {
    SysGFX::ObjectHandle object;
    uint16_t indexCount;
    Pose pose;
    Quanta::Matrix4 transform;
  };

  struct StaticMeshDrawCall {
    SysGFX::ObjectHandle object;
    uint16_t indexCount;
    Quanta::Matrix4 transform;
  };
}

#endif
