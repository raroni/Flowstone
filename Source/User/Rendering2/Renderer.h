#ifndef RENDERING2_RENDERER_H
#define RENDERING2_RENDERER_H

#include "Rendering2/OpenGL/Setup.h"
#include "Rendering2/Culler.h"
#include "Rendering2/CommandBuilder.h"
#include "Rendering2/ObjectList.h"
#include "Rendering2/Config.h"
#include "Rendering2/CommandMerger.h"
#include "Rendering2/AnimatedMeshInstanceList.h"
#include "Rendering2/CommandStream.h"
#include "Rendering2/TransformIndex.h"

struct Pose;

namespace Rendering2 {
  class Renderer {
    AnimatedMeshInstanceList animatedMeshInstanceList;
    ObjectList objectList;
    ObjectIndex visibleBuffer[Config::maxObjects];
    Culler culler;
    CommandStream commandStream;
    CommandBuilder commandBuilder;
    CommandMerger commandMerger;
    Backend backend;
  public:
    Renderer();
    void initialize();
    AnimatedMeshIndex createAnimatedMesh(const AnimatedVertex *vertices, const size_t vertexCount, const uint16_t *indices, const size_t indexCount);
    void createAnimatedMeshInstance(AnimatedMeshIndex meshIndex, TransformIndex transformIndex);
    void draw();
    void setTransforms(const Quanta::Matrix4 *transforms);
    void setPoses(const Pose *poses);
  };
}

#endif