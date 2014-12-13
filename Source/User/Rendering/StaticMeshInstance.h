#ifndef RENDERING_STATIC_MESH_INSTANCE_H
#define RENDERING_STATIC_MESH_INSTANCE_H

#include "Rendering/StaticTransformIndex.h"
#include "Rendering/StaticMeshIndex.h"

namespace Rendering {
  struct StaticMeshInstance {
    StaticMeshIndex mesh;
    StaticTransformIndex transform;
  };
}

#endif
