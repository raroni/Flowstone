#ifndef Rendering_SHADER_REGISTRY_H
#define Rendering_SHADER_REGISTRY_H

#include <stdint.h>
#include <OpenGL/gl3.h>
#include "Conrad/Array.h"
#include "Rendering/ShaderName.h"

namespace Rendering {
  namespace OpenGL {
    typedef size_t ShaderHandle;

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
}

#endif
