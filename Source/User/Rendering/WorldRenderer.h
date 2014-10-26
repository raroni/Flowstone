#ifndef WORLD_RENDERING_RENDERER_H
#define WORLD_RENDERING_RENDERER_H

#include <stddef.h>
#include <OpenGL/gl3.h>
#include "Quanta/Geometry/Transform.h"
#include "Rendering/Vertex.h"

namespace Rendering {
  class ShaderRegistry;

  struct Component {
    Quanta::Transform transform;
    size_t vaoHandle;
    uint16_t indexCount;
  };

  class WorldRenderer {
  public:
    WorldRenderer(ShaderRegistry &registry);
    void initialize();
    size_t createMesh(const Vertex *vertices, const size_t verticesLength, const uint16_t *indices, const size_t indicesLength);
    size_t createComponent(size_t vaoOffset);
    void draw();
    Component* getComponent(size_t index);
    Quanta::Transform cameraTransform;
  private:
    GLint worldViewTransformationUniformHandle;
    GLint modelWorldTransformationUniformHandle;
    GLint positionAttributeHandle;
    Component components[512];
    uint16_t componentsCount = 0;
    GLuint vaoHandles[512];
    uint16_t vaoCount;
    uint16_t indexCounts[512];
    Rendering::ShaderRegistry &shaderRegistry;
  };
}

#endif
