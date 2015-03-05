#ifndef SYSGFX_CULL_FACE_H
#define SYSGFX_CULL_FACE_H

#include <OpenGL/gl3.h>

namespace SysGFX {
  enum class CullFace {
    Front = GL_FRONT,
    Back = GL_BACK
  };
}

#endif
