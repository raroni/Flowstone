#ifndef RENDERING_WORLD_RENDERER_H
#define RENDERING_WORLD_RENDERER_H

#include "Quanta/Geometry/Frustum.h"
#include "Quanta/Geometry/Transform.h"
#include "Rendering/BoneMeshInstance.h"
#include "Rendering/BoneMeshRegistry.h"
#include "Rendering/BoneVertex.h"
#include "Rendering/Culler.h"
#include "Rendering/DrawSet.h"
#include "Rendering/FrustumInfo.h"
#include "Rendering/MeshInfo.h"
#include "Rendering/Shape.h"
#include "Rendering/StaticMeshIndex.h"
#include "Rendering/StaticVertex.h"

namespace Rendering {
  class CommandStream;

  class WorldRenderer {
  public:
    BoneMeshIndex createBoneMesh(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount);
    BoneMeshInstanceIndex createBoneMeshInstance(BoneMeshIndex BoneMeshIndex);
    StaticMeshIndex createStaticMesh(MeshInfo info, const StaticVertex *vertices, const uint16_t *indices, const Shape *shapes);
    StaticMeshInstanceIndex createStaticMeshInstance(StaticMeshIndex mesh);
    void updateStaticMeshTransform(StaticMeshInstanceIndex index, const Quanta::Matrix4 &transform);
    void writeCommands(CommandStream &stream);
    Quanta::Transform cameraTransform;
    void updateResolution(uint16_t width, uint16_t height);
    BoneMeshInstance getBoneMeshInstance(BoneMeshInstanceIndex index);
    Quanta::Vector3 primaryLightDirection;
    Quanta::Vector3 secondaryLightDirection;
    void initialize();
    void setPrimaryLightColor(Quanta::Vector3 color);
  private:
    struct {
      uint16_t width;
      uint16_t height;
    } resolution;
    struct {
      Quanta::Matrix4 worldView;
      Quanta::Matrix4 viewClip;
    } primaryLightTransforms;
    void buildDrawSet(const Quanta::Frustum &frustum);
    Culler culler;
    BoneMeshRegistry boneMeshRegistry;
    DrawSet drawSet;
    Quanta::Matrix4 viewClipTransform;
    void calcViewClipTransform();
    void writeDrawQueueToStream(CommandStream &stream);
    void buildDrawQueue();
    void writeGlobalUniformUpdate(CommandStream &stream, const Quanta::Matrix4 &worldViewTransform);
    Quanta::Frustum localFrustum;
    FrustumInfo frustumInfo;
  };
}

#endif
