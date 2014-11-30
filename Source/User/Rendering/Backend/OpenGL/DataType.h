#include <OpenGL/gl3.h>

namespace Rendering {
  namespace Backend {
    enum class DataType {
      Float = GL_FLOAT,
      UnsignedShort = GL_UNSIGNED_SHORT,
      UnsignedByte = GL_UNSIGNED_BYTE
    };
  }
}
