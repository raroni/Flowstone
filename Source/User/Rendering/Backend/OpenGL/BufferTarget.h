#include <OpenGL/gl3.h>

namespace Rendering {
  namespace Backend {
    enum class BufferTarget {
      Index = GL_ELEMENT_ARRAY_BUFFER,
      Vertex = GL_ARRAY_BUFFER,
      Uniform = GL_UNIFORM_BUFFER
    };
  }
}
