#ifndef RENDERING_WORLD_RENDERER_H
#define RENDERING_WORLD_RENDERER_H

#include "Pose.h"
#include "Quanta/Geometry/Transform.h"
#include "Animation/PoseIndex.h"
#include "Rendering/BoneMeshIndex.h"
#include "Rendering/BoneVertex.h"
#include "Rendering/StaticVertex.h"
#include "Rendering/BoneMeshRegistry.h"
#include "Rendering/StaticTransformIndex.h"
#include "Rendering/DynamicTransformIndex.h"
#include "Rendering/MeshInfo.h"
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
    void createBoneMeshInstance(BoneMeshIndex meshIndex, DynamicTransformIndex transformIndex, Animation::PoseIndex pose);
    StaticMeshIndex createStaticMesh(MeshInfo info, const StaticVertex *vertices, const uint16_t *indices, const Shape *shapes);
    void createStaticMeshInstance(StaticMeshIndex mesh, StaticTransformIndex transform);
    void writeCommands(CommandStream &stream);
    const Quanta::Matrix4* dynamicTransforms;
    const Quanta::Matrix4* staticTransforms;
    const Pose* poses;
    Quanta::Transform cameraTransform;
    void updateResolution(uint16_t width, uint16_t height);
    Quanta::Vector3 lightDirection;
  private:
    struct {
      uint16_t width;
      uint16_t height;
    } resolution;
    BoneMeshRegistry boneMeshRegistry;
    DrawQueue drawQueue;
    void writeShadowMap(CommandStream &stream);
    void writeMerge(CommandStream &stream);
    void writeDrawQueueToStream(CommandStream &stream);
    void buildDrawQueue();
    void writeGlobalUniformUpdate(CommandStream &stream);
  };
}

#endif
