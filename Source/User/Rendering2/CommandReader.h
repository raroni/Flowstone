#ifndef RENDERING2_COMMAND_READER_H
#define RENDERING2_COMMAND_READER_H

#include <stdint.h>
#include "Rendering2/Commands.h"

#include <stdio.h>

namespace Rendering2 {
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
    DrawAnimatedMeshCommand readDrawAnimatedMesh() {
      DrawAnimatedMeshCommand command = *reinterpret_cast<const DrawAnimatedMeshCommand*>(buffer+position);
      position += sizeof(command);
      return command;
    }
  };
}

#endif
