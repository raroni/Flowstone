#ifndef RENDERING2_OPENGL_ANIMATED_MESH_H
#define RENDERING2_OPENGL_ANIMATED_MESH_H

namespace Rendering2 {
  namespace OpenGL {
    struct AnimatedMesh {
      GLuint vaoHandle;
      uint16_t indexCount;
    };
  }
}

#endif
