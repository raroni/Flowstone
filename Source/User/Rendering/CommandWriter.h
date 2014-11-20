#ifndef Rendering_COMMAND_WRITER_H
#define Rendering_COMMAND_WRITER_H

#include <string.h>
#include "Rendering/ShaderName.h"
#include "Rendering/CommandType.h"
#include "Rendering/Commands.h"

namespace Rendering {
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
