#ifndef RENDERING2_COMMAND_TYPE_H
#define RENDERING2_COMMAND_TYPE_H

namespace Rendering2 {
  enum class CommandType {
    DrawAnimatedMesh,
    ChangeShaderProgram,
    UpdateWorldViewTransform
  };
}

#endif
