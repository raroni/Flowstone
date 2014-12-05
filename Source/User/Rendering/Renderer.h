#ifndef RENDERING_RENDERER_H
#define RENDERING_RENDERER_H

#include "Pose.h"
#include "Quanta/Geometry/Transform.h"
#include "Rendering/WorldRenderer.h"
#include "Rendering/BoneMeshIndex.h"
#include "Rendering/StaticMeshIndex.h"
#include "Rendering/BoneVertex.h"
#include "Rendering/MeshInfo.h"
#include "Rendering/Shape.h"
#include "Rendering/CommandStream.h"
#include "Rendering/DynamicTransformIndex.h"
#include "Rendering/StaticTransformIndex.h"

namespace Rendering {
  class Renderer {
  public:
    void initialize();
    BoneMeshIndex createBoneMesh(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount);
    void createBoneMeshInstance(BoneMeshIndex meshIndex, DynamicTransformIndex transformIndex, Animation::PoseIndex pose);
    StaticMeshIndex createStaticMesh(MeshInfo info, const StaticVertex *vertices, const uint16_t *indices, const Shape *shapes);
    void createStaticMeshInstance(StaticMeshIndex mesh, StaticTransformIndex transform);
    void draw();
    void setDynamicTransforms(const Quanta::Matrix4 *transforms);
    void setStaticTransforms(const Quanta::Matrix4 *transforms);
    void setPoses(const Pose *poses);
    Quanta::Transform& getCameraTransform();
    void updateResolution(uint16_t width, uint16_t height);
    void setLightDirection(Quanta::Vector3 lightDirection);
  private:
    CommandStream stream;
    WorldRenderer worldRenderer;
    void dispatch();
  };
}

#endif
