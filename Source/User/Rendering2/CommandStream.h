#ifndef RENDERING2_COMMAND_STREAM_H
#define RENDERING2_COMMAND_STREAM_H

#include <string.h>
#include "Rendering2/ShaderName.h"
#include "Rendering2/CommandType.h"

namespace Rendering2 {
  class CommandStream {
    char buffer[Config::commandBufferSize];
    uint16_t position = 0;
  public:
    void writeType(CommandType type) {
      buffer[position] = *reinterpret_cast<char*>(&type);
      position += sizeof(type);
    }
    void writeShaderName(ShaderName name) {
      buffer[position] = *reinterpret_cast<char*>(&name);
      position += sizeof(name);
    }
    void writeRaw(const void *data, uint16_t length) {
      memcpy(&buffer[position], data, length);
      position += length;
    }
    const char* getBuffer() const {
      return buffer;
    }
    uint16_t getPosition() const {
      return position;
    }
  };
}

#endif
