#ifndef RENDERING_OPENGL_H
#define RENDERING_OPENGL_H

#include "Rendering/BoneMeshIndex.h"
#include "Rendering/BoneVertex.h"
#include "Rendering/BoneMeshIndex.h"

namespace Rendering {
  class OpenGL {
  public:
    static BoneMeshIndex createBoneMesh(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount);
  };
}

#endif
