#include <OpenGL/gl3.h>
#include "Rendering/OpenGL.h"

namespace Rendering {
  BoneMeshIndex OpenGL::createBoneMesh(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount) {
    GLuint handle;
    glGenVertexArrays(1, &handle);
    return static_cast<BoneMeshIndex>(handle);
  }
}
