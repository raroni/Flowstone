#ifndef WORLD_RENDERING_RENDERER_H
#define WORLD_RENDERING_RENDERER_H

#include <stddef.h>
#include <OpenGL/gl.h>
#include "Rendering/Vertex.h"

namespace Rendering {
  class ShaderRegistry;

  struct Component {
    size_t vertexBufferHandle;
    size_t indexBufferHandle;
    float x;
  };

  class WorldRenderer {
  public:
    WorldRenderer(ShaderRegistry &registry);
    void initialize();
    size_t createVertexBuffer(const Vertex *vertices, const size_t length);
    size_t createIndexBuffer(uint16_t *indices, size_t length);
    size_t createComponent(size_t vertexOffset, size_t indexOffset, float x);
    void draw();
    Component* getComponent(size_t index);
    void updateWorldViewTransformation();
  private:
    GLint worldViewTransformationUniformHandle;
    GLint positionAttributeHandle;
    Component components[512];
    uint16_t componentsCount = 0;
    GLuint vertexBufferHandles[512];
    uint16_t vertexBufferHandleCount = 0;
    GLuint indexBufferHandles[512];
    uint16_t indexBufferHandleCount = 0;
    Rendering::ShaderRegistry &shaderRegistry;
  };
}

#endif
