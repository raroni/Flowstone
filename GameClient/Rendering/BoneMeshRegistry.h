#ifndef RENDERING_BONE_MESH_REGISTRY_H
#define RENDERING_BONE_MESH_REGISTRY_H

#include "Rendering/Config.h"
#include "Rendering/BoneMeshIndex.h"
#include "Rendering/BoneVertex.h"
#include "Rendering/Backend/ObjectHandle.h"
#include "Rendering/BoneMesh.h"

namespace Rendering {
  class BoneMeshRegistry {
    Backend::ObjectHandle handles[Config::maxBoneMeshes];
    uint16_t indexCounts[Config::maxBoneMeshes];
    float boundingRadii[Config::maxBoneMeshes];
    uint16_t count = 0;
  public:
    BoneMeshIndex create(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount);
    BoneMesh get(BoneMeshIndex index) const;
  };
}

#endif
