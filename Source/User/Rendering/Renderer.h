#ifndef RENDERING_RENDERER_H
#define RENDERING_RENDERER_H

#include "Pose.h"
#include "Quanta/Geometry/Transform.h"
#include "Rendering/WorldRenderer.h"
#include "Rendering/BoneMeshIndex.h"
#include "Rendering/Resolution.h"
#include "Rendering/StaticMeshIndex.h"
#include "Rendering/BoneVertex.h"
#include "Rendering/MeshInfo.h"
#include "Rendering/Shape.h"
#include "Rendering/CommandStream.h"

namespace Rendering {
  class Renderer {
  public:
    void initialize();
    BoneMeshIndex createBoneMesh(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount);
    BoneMeshInstanceIndex createBoneMeshInstance(BoneMeshIndex meshIndex);
    StaticMeshIndex createStaticMesh(MeshInfo info, const StaticVertex *vertices, const uint16_t *indices, const Shape *shapes);
    StaticMeshInstanceIndex createStaticMeshInstance(StaticMeshIndex mesh);
    PointLightIndex createPointLight();
    void updatePointLightPosition(PointLightIndex index, const Quanta::Vector3 &position);
    BoneMeshInstance getBoneMeshInstance(BoneMeshInstanceIndex index);
    void setPrimaryLightColor(Quanta::Vector3 color);
    void updateStaticMeshTransform(StaticMeshInstanceIndex index, const Quanta::Matrix4 &transform);
    void draw();
    Quanta::Transform& getCameraTransform();
    void updateResolution(Resolution resolution);
    void setPrimaryLightDirection(Quanta::Vector3 lightDirection);
    void setSecondaryLightDirection(Quanta::Vector3 lightDirection);
  private:
    CommandStream stream;
    WorldRenderer worldRenderer;
    void dispatch();
  };
}

#endif
