#ifndef RENDERING_STATIC_MESH_H
#define RENDERING_STATIC_MESH_H

#include "Rendering/Backend/ObjectHandle.h"

namespace Rendering {
  struct StaticMesh {
    Backend::ObjectHandle object;
    uint16_t indexCount;
  };
}

#endif
