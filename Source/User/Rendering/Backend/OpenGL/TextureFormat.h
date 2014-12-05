#include <OpenGL/gl3.h>

namespace Rendering {
  namespace Backend {
    enum class TextureFormat {
      RGB = GL_RGB,
      Red = GL_RED,
      Depth = GL_DEPTH_COMPONENT
    };
  }
}
