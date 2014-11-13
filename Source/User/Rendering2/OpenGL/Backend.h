#include "Core/Error.h"
#include "Rendering2/OpenGL/AnimatedMeshRegistry.h"
#include "Rendering2/OpenGL/ShaderLoading.h"
#include "Rendering2/OpenGL/ShaderRegistry.h"
#include "Rendering2/AnimatedMeshIndex.h"
#include "Rendering2/AnimatedVertex.h"

namespace Rendering2 {
  namespace OpenGL {
    class Backend {
      ShaderRegistry shaderRegistry;
      AnimatedMeshRegistry animatedMeshRegistry;
    public:
      void initialize() {
        loadShaders(shaderRegistry);
        glClearColor(1, 0, 0, 1);
        glEnable(GL_CULL_FACE);
      }
      void configureAnimatedMeshRegistry() {
        GLuint handle = shaderRegistry.getHandle(ShaderName::Animated);
        GLint positionAttributeHandle = glGetAttribLocation(handle, "position");
        if(positionAttributeHandle == -1) {
          fatalError("Could not find position attribute handle.");
        }

        GLint jointIndexAttributeHandle = glGetAttribLocation(handle, "jointIndex");
        if(jointIndexAttributeHandle == -1) {
          fatalError("Could not find joint attribute handle.");
        }

        animatedMeshRegistry.positionAttributeHandle = positionAttributeHandle;
        animatedMeshRegistry.jointIndexAttributeHandle = jointIndexAttributeHandle;
      }
      void clear() {
        glClear(GL_COLOR_BUFFER_BIT);
      }
      AnimatedMeshIndex createAnimatedMesh(const AnimatedVertex *vertices, const size_t vertexCount, const uint16_t *indices, const size_t indexCount) {
        return animatedMeshRegistry.create(vertices, vertexCount, indices, indexCount);
      }
    };
  }
}
