#ifndef RENDERING_BONE_MESH_REGISTRY_H
#define RENDERING_BONE_MESH_REGISTRY_H

#include "Rendering/Config.h"
#include "Rendering/BoneMeshIndex.h"
#include "Rendering/BoneVertex.h"
#include "Rendering/ObjectHandle.h"

namespace Rendering {
  class BoneMeshRegistry {
    ObjectHandle handles[Config::maxBoneMeshes];
    uint16_t indexCounts[Config::maxBoneMeshes];
    uint16_t count = 0;
  public:
    BoneMeshIndex create(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount);
  };
}

#endif
