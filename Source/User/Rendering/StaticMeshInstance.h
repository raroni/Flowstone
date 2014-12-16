#ifndef RENDERING_STATIC_MESH_INSTANCE_H
#define RENDERING_STATIC_MESH_INSTANCE_H

#include "Rendering/StaticMeshIndex.h"
#include "Quanta/Math/Matrix4.h"

namespace Rendering {
  struct StaticMeshInstance {
    StaticMeshIndex mesh;
    Quanta::Matrix4 transform;
  };
}

#endif
