#include <OpenGL/gl3.h>

namespace Rendering {
  namespace Backend {
    enum class TextureFilter {
      Linear = GL_LINEAR,
      Nearest = GL_NEAREST
    };
  }
}
