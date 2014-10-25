#ifndef RENDERING_SHADER_REGISTRY_H
#define RENDERING_SHADER_REGISTRY_H

#include <stdint.h>
#include <OpenGL/gl.h>
#include "Conrad/Array.h"

namespace Rendering {
  typedef size_t ShaderHandle;

  enum class ShaderName {
    Test
  };

  class ShaderRegistry {
    static const uint8_t maxHandlesCount = 20;
    Array<GLuint, maxHandlesCount> handles;
    size_t handlesCount = 0;
    Array<size_t, maxHandlesCount> offsets;
  public:
    void addHandle(ShaderName name, GLuint handle);
    GLuint getHandle(ShaderName name) const;
  };
}

#endif
