#ifndef RENDERING_BACKEND_OPENGL_H
#define RENDERING_BACKEND_OPENGL_H

#include "Rendering/Backend/ObjectHandle.h"
#include "Rendering/Backend/BoneVertex.h"

namespace Rendering {
  namespace Backend {
    namespace OpenGL {
      ObjectHandle createBoneMesh(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount);
    }
  }
}

#endif
