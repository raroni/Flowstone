#include <OpenGL/gl3.h>

namespace Rendering {
  namespace Backend {
    enum class ClearBit {
      Color = GL_COLOR_BUFFER_BIT,
      Depth = GL_DEPTH_BUFFER_BIT
    };
  }
}
