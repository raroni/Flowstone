#ifndef RENDERING_STATIC_MESH_H
#define RENDERING_STATIC_MESH_H

#include "SysGFX/ObjectHandle.h"

namespace Rendering {
  struct StaticMesh {
    SysGFX::ObjectHandle object;
    uint16_t indexCount;
    float boundingRadius;
  };
}

#endif
