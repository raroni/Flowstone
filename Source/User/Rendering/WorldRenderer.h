#ifndef WORLD_RENDERING_RENDERER_H
#define WORLD_RENDERING_RENDERER_H

#include <stddef.h>
#include <OpenGL/gl3.h>
#include "Quanta/Geometry/Transform.h"
#include "Rendering/AnimatedVertex.h"

namespace Animation {
  struct Pose;
}

namespace Rendering {
  class ShaderRegistry;

  struct AnimatedMeshInstance {
    Quanta::Transform transform;
    size_t vaoHandle;
    uint16_t indexCount;
    uint8_t skeletonInstanceID;
  };

  class WorldRenderer {
  public:
    WorldRenderer(ShaderRegistry &registry);
    void initialize();
    size_t createAnimatedMesh(const AnimatedVertex *vertices, const size_t verticesLength, const uint16_t *indices, const size_t indicesLength);
    size_t createAnimatedMeshInstance(size_t vaoOffset, uint8_t skeletonInstanceID);
    void draw(const Animation::Pose *poses);
    AnimatedMeshInstance* getAnimatedMeshInstance(size_t index);
    Quanta::Transform cameraTransform;
  private:
    GLint worldViewTransformationUniformHandle;
    GLint jointWorldTransformationUniformHandle;
    GLint modelJointTransformationsUniformHandle;
    GLint positionAttributeHandle;
    GLint jointIndexAttributeHandle;
    AnimatedMeshInstance animatedMeshInstances[512];
    uint16_t animatedMeshInstanceCount = 0;
    GLuint vaoHandles[512];
    uint16_t vaoCount;
    uint16_t indexCounts[512];
    Rendering::ShaderRegistry &shaderRegistry;
  };
}

#endif
