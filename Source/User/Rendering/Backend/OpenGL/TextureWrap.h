#include <OpenGL/gl3.h>

namespace Rendering {
  namespace Backend {
    enum class TextureWrap {
      Clamp = GL_CLAMP_TO_EDGE,
      Repeat = GL_REPEAT
    };
  }
}
