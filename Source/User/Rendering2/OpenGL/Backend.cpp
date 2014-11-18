#include "Core/Error.h"
#include "Rendering2/CommandType.h"
#include "Rendering2/OpenGL/ShaderLoading.h"
#include "Rendering2/OpenGL/Backend.h"

#include <stdio.h>

namespace Rendering2 {
  namespace OpenGL {
    void Backend::initialize() {
        loadShaders(shaderRegistry);
        glClearColor(1, 0, 0, 1);
        glEnable(GL_CULL_FACE);
      }

    void Backend::configureAnimatedMeshRegistry() {
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

    void Backend::clear() {
      glClear(GL_COLOR_BUFFER_BIT);
    }

    AnimatedMeshIndex Backend::createAnimatedMesh(const AnimatedVertex *vertices, const size_t vertexCount, const uint16_t *indices, const size_t indexCount) {
      return animatedMeshRegistry.create(vertices, vertexCount, indices, indexCount);
    }

    void Backend::draw(const char *stream, uint16_t count) {
      printf("Running %d commands\n", count);
      for(uint16_t i=0; count>i; i++) {
        CommandType type = *reinterpret_cast<const CommandType*>(stream);
        printf("Type as int: %d\n", static_cast<int>(type));
        switch(type) {
          case CommandType::ChangeShaderProgram:
            printf("ChangeShaderProgram!\n");
            break;
          case CommandType::DrawAnimatedMesh:
            printf("DrawAnimatedMesh!\n");
            break;
          default:
            fatalError("Could not execute command.");
            break;
        }
      }
    }
  }
}
