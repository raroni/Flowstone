#ifndef Rendering_COMMAND_READER_H
#define Rendering_COMMAND_READER_H

#include <stdint.h>
#include "Rendering/Commands.h"

namespace Rendering {
  class CommandReader {
    const char *buffer;
    uint16_t position = 0;
  public:
    CommandReader(const char *buffer) : buffer(buffer) { }
    CommandType readType() {
      CommandType type = *reinterpret_cast<const CommandType*>(buffer+position);
      position += sizeof(CommandType);
      return type;
    }
    ChangeShaderProgramCommand readChangeShaderProgram() {
      ChangeShaderProgramCommand command = *reinterpret_cast<const ChangeShaderProgramCommand*>(buffer+position);
      position += sizeof(command);
      return command;
    }
    UpdateWorldViewTransformCommand readUpdateWorldViewTransform() {
      UpdateWorldViewTransformCommand command = *reinterpret_cast<const UpdateWorldViewTransformCommand*>(buffer+position);
      position += sizeof(command);
      return command;
    }
    DrawAnimatedMeshCommand readDrawAnimatedMesh() {
      DrawAnimatedMeshCommand command = *reinterpret_cast<const DrawAnimatedMeshCommand*>(buffer+position);
      position += sizeof(command);
      return command;
    }
  };
}

#endif
