#ifndef RENDERING_BONE_MESH_H
#define RENDERING_BONE_MESH_H

#include "SysGFX/ObjectHandle.h"

namespace Rendering {
  struct BoneMesh {
    SysGFX::ObjectHandle object;
    uint16_t indexCount;
    float boundingRadius;
  };
}

#endif
