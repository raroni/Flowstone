#ifndef RENDERING_WORLD_RENDERER_H
#define RENDERING_WORLD_RENDERER_H

#include "Pose.h"
#include "Rendering/BoneMeshIndex.h"
#include "Rendering/BoneVertex.h"
#include "Rendering/BoneMeshRegistry.h"
#include "Rendering/TransformIndex.h"
#include "Rendering/DrawQueue.h"
#include "Rendering/Config.h"

namespace Rendering {
  class CommandStream;

  class WorldRenderer {
  public:
    BoneMeshIndex createBoneMesh(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount);
    void createBoneMeshInstance(BoneMeshIndex meshIndex, TransformIndex transformIndex);
    void writeCommands(CommandStream &stream);
    const Quanta::Matrix4* transforms;
    const Pose* poses;
  private:
    BoneMeshRegistry boneMeshRegistry;
    DrawQueue drawQueue;
    void writeDrawQueueToStream(CommandStream &stream);
    void buildDrawQueue();
  };
}

#endif
