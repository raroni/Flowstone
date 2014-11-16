#ifndef RENDERING2_OPENGL_BACKEND_H
#define RENDERING2_OPENGL_BACKEND_H

#include "Rendering2/AnimatedMeshIndex.h"
#include "Rendering2/AnimatedVertex.h"
#include "Rendering2/OpenGL/ShaderRegistry.h"
#include "Rendering2/OpenGL/AnimatedMeshRegistry.h"

namespace Rendering2 {
  namespace OpenGL {
    class Backend {
    public:
      void initialize();
      void configureAnimatedMeshRegistry();
      void clear();
      AnimatedMeshIndex createAnimatedMesh(const AnimatedVertex *vertices, const size_t vertexCount, const uint16_t *indices, const size_t indexCount);
      void draw(const char *stream, uint16_t count);
    private:
      ShaderRegistry shaderRegistry;
      AnimatedMeshRegistry animatedMeshRegistry;
    };
  }
}

#endif
