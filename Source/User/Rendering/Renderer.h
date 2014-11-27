#ifndef RENDERING_RENDERER_H
#define RENDERING_RENDERER_H

#include "Pose.h"
#include "Quanta/Geometry/Transform.h"
#include "Rendering/WorldRenderer.h"
#include "Rendering/BoneMeshIndex.h"
#include "Rendering/BoneVertex.h"
#include "Rendering/TransformIndex.h"

namespace Rendering {
  class Renderer {
    WorldRenderer worldRenderer;
  public:
    void initialize();
    BoneMeshIndex createBoneMesh(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount);
    void createBoneMeshInstance(BoneMeshIndex meshIndex, TransformIndex transformIndex);
    void draw();
    void setTransforms(const Quanta::Matrix4 *transforms);
    void setPoses(const Pose *poses);
    Quanta::Transform cameraTransform;
  };
}

#endif