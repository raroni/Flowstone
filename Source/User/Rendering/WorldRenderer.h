#ifndef WORLD_RENDERING_RENDERER_H
#define WORLD_RENDERING_RENDERER_H

#include <stddef.h>
#include <OpenGL/gl.h>
#include "Quanta/Geometry/Transform.h"
#include "Rendering/Vertex.h"

namespace Rendering {
  class ShaderRegistry;

  struct Component {
    Quanta::Transform transform;
    size_t vertexBufferHandle;
    size_t indexBufferHandle;
    uint16_t indexBufferLength;
  };

  class WorldRenderer {
  public:
    WorldRenderer(ShaderRegistry &registry);
    void initialize();
    size_t createVertexBuffer(const Vertex *vertices, const size_t length);
    size_t createIndexBuffer(uint16_t *indices, size_t length);
    size_t createComponent(size_t vertexOffset, size_t indexOffset);
    void draw();
    Component* getComponent(size_t index);
    Quanta::Transform cameraTransform;
  private:
    GLint worldViewTransformationUniformHandle;
    GLint modelWorldTransformationUniformHandle;
    GLint positionAttributeHandle;
    Component components[512];
    uint16_t componentsCount = 0;
    GLuint vertexBufferHandles[512];
    uint16_t vertexBufferHandleCount = 0;
    GLuint indexBufferHandles[512];
    uint16_t indexBufferLengths[512];
    uint16_t indexBufferHandleCount = 0;
    Rendering::ShaderRegistry &shaderRegistry;
  };
}

#endif
