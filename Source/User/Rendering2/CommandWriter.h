#ifndef RENDERING2_COMMAND_WRITER_H
#define RENDERING2_COMMAND_WRITER_H

#include <string.h>
#include "Rendering2/ShaderName.h"
#include "Rendering2/CommandType.h"
#include "Rendering2/Commands.h"

namespace Rendering2 {
  class CommandWriter {
    uint16_t position = 0;
    char *buffer;
  public:
    CommandWriter(char *buffer) : buffer(buffer) { }
    void writeType(CommandType type) {
      memcpy(buffer+position, &type, sizeof(type));
      position += sizeof(type);
    }
    void writeChangeShaderProgram(ChangeShaderProgramCommand command) {
      memcpy(buffer+position, &command, sizeof(command));
      position += sizeof(command);
    }
    void writeDrawAnimatedMesh(DrawAnimatedMeshCommand command) {
      memcpy(buffer+position, &command, sizeof(command));
      position += sizeof(command);
    }
    void writeUpdateWorldViewTransform(UpdateWorldViewTransformCommand command) {
      memcpy(buffer+position, &command, sizeof(command));
      position += sizeof(command);
    }
    void writeRaw(const void *data, uint16_t length) {
      memcpy(&buffer[position], data, length);
      position += length;
    }
    uint16_t getPosition() const {
      return position;
    }
    void reset() {
      position = 0;
    }
  };
}

#endif