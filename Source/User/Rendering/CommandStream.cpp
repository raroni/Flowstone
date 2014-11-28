#include <string.h>
#include "Rendering/CommandStream.h"

namespace Rendering {
  void CommandStream::writeIndexedDraw(IndexedDrawCommand command) {
    writeType(CommandType::IndexedDraw);
    memcpy(buffer+position, &command, sizeof(command));
    position += sizeof(command);
  }

  void CommandStream::writeObjectSet(ObjectSetCommand command) {
    writeType(CommandType::Uniform8Mat4Set);
    memcpy(buffer+position, &command, sizeof(command));
    position += sizeof(command);
  }

  void CommandStream::writeProgramSet(ProgramSetCommand command) {
    writeType(CommandType::ProgramSet);
    memcpy(buffer+position, &command, sizeof(command));
    position += sizeof(command);
  }

  void CommandStream::writeUniformMat4Set(UniformMat4SetCommand command) {
    writeType(CommandType::UniformMat4Set);
    memcpy(buffer+position, &command, sizeof(command));
    position += sizeof(command);
  }

  void CommandStream::writeUniform8Mat4Set(Uniform8Mat4SetCommand command) {
    writeType(CommandType::Uniform8Mat4Set);
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

  IndexedDrawCommand CommandStream::readIndexedDraw() {
    IndexedDrawCommand command = *reinterpret_cast<const IndexedDrawCommand*>(buffer+position);
    position += sizeof(command);
    return command;
  }

  ObjectSetCommand CommandStream::readObjectSet() {
    ObjectSetCommand command = *reinterpret_cast<const ObjectSetCommand*>(buffer+position);
    position += sizeof(command);
    return command;
  }

  ProgramSetCommand CommandStream::readProgramSet() {
    ProgramSetCommand command = *reinterpret_cast<const ProgramSetCommand*>(buffer+position);
    position += sizeof(command);
    return command;
  }

  UniformMat4SetCommand CommandStream::readUniformMat4Set() {
    UniformMat4SetCommand command = *reinterpret_cast<const UniformMat4SetCommand*>(buffer+position);
    position += sizeof(command);
    return command;
  }

  Uniform8Mat4SetCommand CommandStream::readUniform8Mat4Set() {
    Uniform8Mat4SetCommand command = *reinterpret_cast<const Uniform8Mat4SetCommand*>(buffer+position);
    position += sizeof(command);
    return command;
  }
}
