#ifndef Rendering_OPENGL_ANIMATED_MESH_H
#define Rendering_OPENGL_ANIMATED_MESH_H

namespace Rendering {
  namespace OpenGL {
    struct BoneMesh {
      GLuint vaoHandle;
      uint16_t indexCount;
    };
  }
}

#endif
