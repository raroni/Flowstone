#ifndef WORLD_RENDERING_RENDERER_H
#define WORLD_RENDERING_RENDERER_H

#include <stddef.h>
#include <OpenGL/GL.h>
#include "WorldRendering/Vertex.h"

class ShaderRegistry;

namespace WorldRendering {
  struct Component {
    size_t vertexBufferHandle;
    size_t indexBufferHandle;
    float x;
  };
  
  class Renderer {
  public:
    Renderer(ShaderRegistry &registry);
    void initialize();
    size_t createVertexBuffer(const Vertex *vertices, const size_t length);
    size_t createIndexBuffer(uint16_t *indices, size_t length);
    size_t createComponent(size_t vertexOffset, size_t indexOffset, float x);
    void draw();
    Component* getComponent(size_t index);
  private:
    GLint positionAttributeHandle;
    Component components[512];
    uint16_t componentsCount = 0;
    GLuint vertexBufferHandles[512];
    uint16_t vertexBufferHandleCount = 0;
    GLuint indexBufferHandles[512];
    uint16_t indexBufferHandleCount = 0;
    ShaderRegistry &shaderRegistry;
  };
}

#endif
