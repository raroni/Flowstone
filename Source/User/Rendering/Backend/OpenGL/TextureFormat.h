#include <OpenGL/gl3.h>

namespace Rendering {
  namespace Backend {
    enum class TextureFormat {
      RGB = GL_RGB,
      SignedNormalizedRGB = GL_RGB8_SNORM,
      Red = GL_RED,
      Depth = GL_DEPTH_COMPONENT
    };
  }
}
