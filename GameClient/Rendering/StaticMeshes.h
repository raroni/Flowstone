#ifndef RENDERING_STATIC_MESHES_H
#define RENDERING_STATIC_MESHES_H

#include "Rendering/StaticMeshIndex.h"
#include "Rendering/StaticVertex.h"
#include "Rendering/MeshInfo.h"
#include "Rendering/Shape.h"
#include "Rendering/StaticMesh.h"

namespace Rendering {
  namespace StaticMeshes {
    StaticMeshIndex create(MeshInfo info, const StaticVertex *vertices, const uint16_t *indices, const Shape *shapes);
    const StaticMesh& get(StaticMeshIndex index);
  }
}

#endif
