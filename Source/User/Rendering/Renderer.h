#ifndef Rendering_RENDERER_H
#define Rendering_RENDERER_H

#include "Rendering/OpenGL/Setup.h"
#include "Rendering/Culler.h"
#include "Rendering/CommandBuilder.h"
#include "Rendering/ObjectList.h"
#include "Rendering/Config.h"
#include "Rendering/CommandMerger.h"
#include "Rendering/AnimatedMeshInstanceList.h"
#include "Rendering/CommandSorter.h"
#include "Rendering/TransformIndex.h"

struct Pose;

namespace Rendering {
  class Renderer {
    AnimatedMeshInstanceList animatedMeshInstanceList;
    ObjectList objectList;
    ObjectIndex visibleBuffer[Config::maxObjects];
    Culler culler;
    CommandBuilder commandBuilder;
    CommandSorter commandSorter;
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
    Quanta::Transform cameraTransform;
  };
}

#endif