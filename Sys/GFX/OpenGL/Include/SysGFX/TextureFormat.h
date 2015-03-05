#include <OpenGL/gl3.h>

namespace SysGFX {
  enum class TextureFormat {
    RGB = GL_RGB,
    RGBA = GL_RGBA,
    SignedNormalizedRGB = GL_RGB8_SNORM,
    RedF32 = GL_R32F,
    RedGreenF32 = GL_RG32F,
    Red = GL_RED,
    Depth = GL_DEPTH_COMPONENT32F
  };
}
