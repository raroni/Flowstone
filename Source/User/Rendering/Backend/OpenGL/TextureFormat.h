#include <OpenGL/gl3.h>

namespace Rendering {
  namespace Backend {
    enum class TextureFormat {
      RGB = GL_RGB,
      SignedNormalizedRGB = GL_RGB8_SNORM,
      RedF32 = GL_R32F,
      RedGreenF16 = GL_RG16F,
      Red = GL_RED,
      Depth = GL_DEPTH_COMPONENT32F
    };
  }
}
