#ifndef Rendering_COMMAND_TYPE_H
#define Rendering_COMMAND_TYPE_H

namespace Rendering {
  enum class CommandType {
    DrawBoneMesh,
    ChangeShaderProgram,
    UpdateWorldViewTransform
  };
}

#endif
