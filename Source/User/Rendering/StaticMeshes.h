#ifndef RENDERING_STATIC_MESHES_H
#define RENDERING_STATIC_MESHES_H

#include "Rendering/StaticMeshIndex.h"
#include "Rendering/StaticVertex.h"
#include "Rendering/StaticMesh.h"

namespace Rendering {
  namespace StaticMeshes {
    StaticMeshIndex create(const StaticVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount);
    const StaticMesh& get(StaticMeshIndex index);
  }
}

#endif
