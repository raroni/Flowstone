#include "Rendering/OpenGL/ShaderRegistry.h"

namespace Rendering {
  namespace OpenGL {
    void ShaderRegistry::addHandle(ShaderName name, GLuint handle) {
      handles[handlesCount] = handle;
      offsets[static_cast<size_t>(name)] = handlesCount;
      handlesCount++;
    }

    GLuint ShaderRegistry::getHandle(ShaderName name) const {
      size_t offset = offsets[static_cast<size_t>(name)];
      return handles[offset];
    }
  }
}
