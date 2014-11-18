#ifndef RENDERING2_COMMANDS_H
#define RENDERING2_COMMANDS_H

#include "Quanta/Math/Matrix4.h"
#include "Pose.h"
#include "Rendering2/AnimatedMeshIndex.h"
#include "Rendering2/ShaderName.h"

namespace Rendering2 {
  struct DrawAnimatedMeshCommand {
    AnimatedMeshIndex meshIndex;
    Quanta::Matrix4 transform;
    Pose pose;
  };

  struct ChangeShaderProgramCommand {
    ShaderName shader;
  };
}

#endif
