#ifndef RENDERING_WORLD_RENDERER_H
#define RENDERING_WORLD_RENDERER_H

#include "Quanta/Geometry/Transform.h"
#include "Quanta/Geometry/Frustum.h"
#include "Animation/PoseIndex.h"
#include "Rendering/BoneMeshIndex.h"
#include "Rendering/BoneVertex.h"
#include "Rendering/Culler.h"
#include "Rendering/BoneMeshInstance.h"
#include "Rendering/StaticVertex.h"
#include "Rendering/BoneMeshRegistry.h"
#include "Rendering/MeshInfo.h"
#include "Rendering/DrawSet.h"
#include "Rendering/CullResult.h"
#include "Rendering/Shape.h"
#include "Rendering/StaticMeshIndex.h"
#include "Rendering/DrawQueue.h"
#include "Rendering/Backend/BufferHandle.h"
#include "Rendering/Config.h"

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
    Quanta::Vector3 lightDirection;
    void initialize();
  private:
    struct {
      uint16_t width;
      uint16_t height;
    } resolution;
    struct {
      Quanta::Matrix4 worldView;
      Quanta::Matrix4 viewClip;
    } lightTransforms;
    void buildDrawSet();
    Culler culler;
    CullResult cullResult;
    BoneMeshRegistry boneMeshRegistry;
    DrawQueue drawQueue;
    DrawSet drawSet;
    void calcLightTransforms();
    Quanta::Matrix4 calcViewClipTransform() const;
    void writeShadowMap(CommandStream &stream);
    void writeMerge(CommandStream &stream);
    void writeDrawQueueToStream(CommandStream &stream);
    void buildDrawQueue();
    void writeGlobalUniformUpdate(CommandStream &stream);
    Quanta::Frustum calcFrustum() const;
  };
}

#endif
