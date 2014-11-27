#ifndef RENDERING_WORLD_RENDERER_H
#define RENDERING_WORLD_RENDERER_H

#include "Rendering/BoneMeshIndex.h"
#include "Rendering/BoneVertex.h"
#include "Rendering/BoneMeshRegistry.h"
#include "Rendering/TransformIndex.h"
#include "Rendering/Config.h"

namespace Rendering {
  class WorldRenderer {
    BoneMeshRegistry boneMeshRegistry;
  public:
    BoneMeshIndex createBoneMesh(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount);
    void createBoneMeshInstance(BoneMeshIndex meshIndex, TransformIndex transformIndex);
  };
}

#endif
