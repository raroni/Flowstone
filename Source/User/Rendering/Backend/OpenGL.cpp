#include <OpenGL/gl3.h>
#include "Rendering/Backend/OpenGL.h"

namespace Rendering {
  namespace Backend {
    namespace OpenGL {
      ObjectHandle createBoneMesh(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount) {
        GLuint handle;
        glGenVertexArrays(1, &handle);
        return static_cast<ObjectHandle>(handle);
      }
    }
  }
}
