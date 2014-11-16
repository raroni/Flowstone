#ifndef RENDERING2_COMMAND_BUILDER_H
#define RENDERING2_COMMAND_BUILDER_H

#include "Rendering2/ShaderName.h"
#include "Rendering2/AnimatedMeshInstanceIndex.h"
#include "Rendering2/ObjectIndex.h"

namespace Quanta {
  class Matrix4;
}

struct Pose;

namespace Rendering2 {
  class CommandStream;
  class AnimatedMeshInstanceList;
  struct Object;

  class CommandBuilder {
  public:
    CommandBuilder(CommandStream &commandStream, AnimatedMeshInstanceList &animatedMeshInstanceList);
    void build(const Object *objects, const ObjectIndex *indices, uint16_t count);
    const Quanta::Matrix4 *transforms;
    const Pose *poses;
  private:
    CommandStream &stream;
    AnimatedMeshInstanceList &animatedMeshInstanceList;
    void enqueueAnimatedMeshInstanceDraw(AnimatedMeshInstanceIndex index);
    void enqueueShaderProgramChange(ShaderName shader);
  };
}

#endif
