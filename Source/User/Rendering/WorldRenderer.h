#ifndef WORLD_RENDERING_RENDERER_H
#define WORLD_RENDERING_RENDERER_H

#include <stddef.h>
#include <OpenGL/gl3.h>
#include "Quanta/Geometry/Transform.h"
#include "Rendering/AnimatedVertex.h"

struct Pose;

namespace Rendering {
  class ShaderRegistry;

  struct AnimatedMeshInstance {
    uint8_t interpolationTransformID;
    size_t vaoHandle;
    uint16_t indexCount;
  };

  class WorldRenderer {
  public:
    WorldRenderer(ShaderRegistry &registry);
    void initialize();
    size_t createAnimatedMesh(const AnimatedVertex *vertices, const size_t verticesLength, const uint16_t *indices, const size_t indicesLength);
    size_t createAnimatedMeshInstance(size_t vaoOffset, uint8_t interpolationTransformID);
    void draw();
    AnimatedMeshInstance* getAnimatedMeshInstance(size_t index);
    Quanta::Transform cameraTransform;
    void setPoses(const Pose *poses);
    void setJointWorldTransformations(const Quanta::Matrix4 *transforms);
  private:
    const Pose *poses;
    const Quanta::Matrix4 *jointWorldTransformations;
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
