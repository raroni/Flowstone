#ifndef RENDERING_RENDERER_H
#define RENDERING_RENDERER_H

#include "Quanta/Geometry/Transform.h"
#include "Rendering/BoneMeshIndex.h"
#include "Rendering/BoneMeshDraw.h"
#include "Rendering/BoneMeshDrawHandle.h"
#include "Rendering/StaticVertex.h"
#include "Rendering/StaticMeshDrawHandle.h"
#include "Rendering/PointLightHandle.h"
#include "Rendering/Resolution.h"
#include "Rendering/StaticMeshIndex.h"
#include "Rendering/BoneVertex.h"
#include "Rendering/MeshInfo.h"
#include "Rendering/Shape.h"

namespace Rendering {
  namespace Renderer {
    void initialize();
    BoneMeshIndex createBoneMesh(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount);
    BoneMeshDrawHandle createBoneMeshDraw(BoneMeshIndex meshIndex);
    StaticMeshIndex createStaticMesh(MeshInfo info, const StaticVertex *vertices, const uint16_t *indices, const Shape *shapes);
    StaticMeshDrawHandle createStaticMeshDraw(StaticMeshIndex mesh);
    PointLightHandle createPointLight();
    void updatePointLightPosition(PointLightHandle handle, const Quanta::Vector3 &position);
    BoneMeshDraw getBoneMeshDraw(BoneMeshDrawHandle handle);
    void setPrimaryLightColor(Quanta::Vector3 color);
    void updateStaticMeshTransform(StaticMeshDrawHandle handle, const Quanta::Matrix4 &transform);
    void draw();
    Quanta::Transform& getCameraTransform();
    void updateResolution(Resolution resolution);
    void setPrimaryLightDirection(Quanta::Vector3 lightDirection);
    void setSecondaryLightDirection(Quanta::Vector3 lightDirection);
  }
}

#endif
