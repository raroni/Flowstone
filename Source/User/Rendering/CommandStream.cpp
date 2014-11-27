#include <string.h>
#include "Rendering/CommandStream.h"

namespace Rendering {
  void CommandStream::writeProgramChange(ProgramChangeCommand command) {
    writeType(CommandType::ProgramChange);
    memcpy(buffer+position, &command, sizeof(command));
    position += sizeof(command);
  }

  void CommandStream::writeType(CommandType type) {
    count++;
    memcpy(buffer+position, &type, sizeof(type));
    position += sizeof(type);
  }

  void CommandStream::reset() {
    count = 0;
    rewind();
  }

  void CommandStream::rewind() {
    position = 0;
  }

  CommandType CommandStream::readType() {
    CommandType type = *reinterpret_cast<const CommandType*>(buffer+position);
    position += sizeof(CommandType);
    return type;
  }

  ProgramChangeCommand CommandStream::readProgramChange() {
    ProgramChangeCommand command = *reinterpret_cast<const ProgramChangeCommand*>(buffer+position);
    position += sizeof(command);
    return command;
  }
}
