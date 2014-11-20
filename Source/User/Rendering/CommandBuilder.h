#ifndef Rendering_COMMAND_BUILDER_H
#define Rendering_COMMAND_BUILDER_H

#include "Quanta/Geometry/Transform.h"
#include "Rendering/ShaderName.h"
#include "Rendering/AnimatedMeshInstanceIndex.h"
#include "Rendering/ObjectIndex.h"

namespace Quanta {
  class Matrix4;
}

struct Pose;

namespace Rendering {
  class CommandSorter;
  class AnimatedMeshInstanceList;
  struct Object;

  class CommandBuilder {
  public:
    CommandBuilder(CommandSorter &commandSorter, AnimatedMeshInstanceList &animatedMeshInstanceList, Quanta::Transform &cameraTransform);
    void build(const Object *objects, const ObjectIndex *indices, uint16_t count);
    const Quanta::Matrix4 *transforms;
    const Pose *poses;
  private:
    CommandSorter &commandSorter;
    AnimatedMeshInstanceList &animatedMeshInstanceList;
    Quanta::Transform &cameraTransform;
    void enqueueAnimatedMeshInstanceDraw(AnimatedMeshInstanceIndex index);
    void enqueueShaderProgramChange(ShaderName shader);
    void enqueueUpdateWorldViewTransform();
  };
}

#endif
