#ifndef RENDERING2_COMMAND_SIZES_H
#define RENDERING2_COMMAND_SIZES_H

#include "Rendering2/Commands.h"
#include "Rendering2/CommandType.h"

namespace Rendering2 {
  uint8_t commandSizes[Config::maxCommandTypes];
  commandSizes[CommandType::DrawAnimatedMesh] = sizeof(DrawAnimatedMeshCommand);
  commandSizes[CommandType::ChangeShaderProgram] = sizeof(ChangeShaderProgramCommand);
}

#endif
