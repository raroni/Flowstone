#include "Rendering/Backend.h"
#include "Rendering/WorldRenderer.h"

namespace Rendering {
  BoneMeshIndex WorldRenderer::createBoneMesh(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount) {
    BoneMeshIndex index = Backend::createBoneMesh(vertices, vertexCount, indices, indexCount);
    boneMeshIndexCounts[index] = indexCount;
    return index;
  }
}
