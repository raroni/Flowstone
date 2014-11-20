#ifndef Rendering_COMMANDS_H
#define Rendering_COMMANDS_H

#include "Quanta/Math/Matrix4.h"
#include "Pose.h"
#include "Rendering/BoneMeshIndex.h"
#include "Rendering/ShaderName.h"

namespace Rendering {
  struct DrawBoneMeshCommand {
    BoneMeshIndex meshIndex;
    Quanta::Matrix4 transform;
    Pose pose;
  };

  struct ChangeShaderProgramCommand {
    ShaderName shader;
  };

  struct UpdateWorldViewTransformCommand {
    float matrix[16];
  };
}

#endif
