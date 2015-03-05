#ifndef SysGFX_BUFFER_TARGET_H
#define SysGFX_BUFFER_TARGET_H

#include <OpenGL/gl3.h>

namespace SysGFX {
  enum class BufferTarget {
    Index = GL_ELEMENT_ARRAY_BUFFER,
    Vertex = GL_ARRAY_BUFFER,
    Uniform = GL_UNIFORM_BUFFER
  };
}

#endif
