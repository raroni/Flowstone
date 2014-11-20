#ifndef Rendering_OPENGL_BACKEND_H
#define Rendering_OPENGL_BACKEND_H

#include "Rendering/AnimatedMeshIndex.h"
#include "Rendering/AnimatedVertex.h"
#include "Rendering/OpenGL/ShaderRegistry.h"
#include "Rendering/OpenGL/AnimatedMeshRegistry.h"

namespace Rendering {
  namespace OpenGL {
    class Backend {
    public:
      void initialize();
      void configureAnimatedMeshRegistry();
      void clear();
      AnimatedMeshIndex createAnimatedMesh(const AnimatedVertex *vertices, const size_t vertexCount, const uint16_t *indices, const size_t indexCount);
      void draw(const char *stream, uint16_t count);
    private:
      GLint worldViewTransformationUniformHandle;
      GLint jointWorldTransformationUniformHandle;
      GLint modelJointTransformationsUniformHandle;
      GLint positionAttributeHandle;
      GLint jointIndexAttributeHandle;
      ShaderRegistry shaderRegistry;
      AnimatedMeshRegistry animatedMeshRegistry;
    };
  }
}

#endif
