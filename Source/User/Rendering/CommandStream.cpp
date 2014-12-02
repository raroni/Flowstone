#include <string.h>
#include "Rendering/CommandStream.h"

namespace Rendering {
  void CommandStream::writeBufferSet(Backend::BufferTarget target, Backend::BufferHandle buffer) {
    writeType(CommandType::BufferSet);
    BufferSetCommand command;
    command.target = target;
    command.buffer = buffer;
    memcpy(this->buffer+position, &command, sizeof(command));
    position += sizeof(command);
  }

  void CommandStream::writeBufferWrite(Backend::BufferTarget target, uint16_t size, const void *data) {
    writeType(CommandType::BufferWrite);
    BufferWriteCommand command;
    command.target = target;
    command.size = size;
    memcpy(buffer+position, &command, sizeof(command));
    position += sizeof(command);
    memcpy(buffer+position, data, size);
    position += size;
  }

  void CommandStream::writeClear(Backend::ClearBitMask mask) {
    writeType(CommandType::Clear);
    ClearCommand command;
    command.mask = mask;
    memcpy(buffer+position, &command, sizeof(command));
    position += sizeof(command);
  }

  void CommandStream::writeDisableDepthTest() {
    writeType(CommandType::DisableDepthTest);
  }

  void CommandStream::writeEnableDepthTest() {
    writeType(CommandType::EnableDepthTest);
  }

  void CommandStream::writeIndexedDraw(uint16_t indexCount, Backend::DataType dataType) {
    writeType(CommandType::IndexedDraw);
    IndexedDrawCommand command;
    command.indexCount = indexCount;
    command.dataType = dataType;
    memcpy(buffer+position, &command, sizeof(command));
    position += sizeof(command);
  }

  void CommandStream::writeObjectSet(Backend::ObjectHandle object) {
    writeType(CommandType::ObjectSet);
    ObjectSetCommand command;
    command.object = object;
    memcpy(buffer+position, &command, sizeof(command));
    position += sizeof(command);
  }

  void CommandStream::writeProgramSet(Backend::ProgramHandle program) {
    writeType(CommandType::ProgramSet);
    ProgramSetCommand command;
    command.program = program;
    memcpy(buffer+position, &command, sizeof(command));
    position += sizeof(command);
  }

  void CommandStream::writeRenderTargetSet(Backend::RenderTargetHandle renderTarget) {
    writeType(CommandType::RenderTargetSet);
    RenderTargetSetCommand command;
    command.renderTarget = renderTarget;
    memcpy(buffer+position, &command, sizeof(command));
    position += sizeof(command);
  }

  void CommandStream::writeTextureSet(Backend::UniformHandle uniform, Backend::TextureHandle texture, uint8_t unit) {
    writeType(CommandType::TextureSet);
    TextureSetCommand command;
    command.uniform = uniform;
    command.texture = texture;
    command.unit = unit;
    memcpy(buffer+position, &command, sizeof(command));
    position += sizeof(command);
  }

  void CommandStream::writeUniformMat4Set(Backend::UniformHandle uniform, uint16_t count, const float *data) {
    writeType(CommandType::UniformMat4Set);
    UniformMat4SetCommand command;
    command.uniform = uniform;
    command.count = count;
    memcpy(buffer+position, &command, sizeof(command));
    position += sizeof(command);
    size_t dataSize = count*sizeof(float)*16;
    memcpy(buffer+position, data, dataSize);
    position += dataSize;
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

  BufferSetCommand CommandStream::readBufferSet() {
    BufferSetCommand command = *reinterpret_cast<const BufferSetCommand*>(buffer+position);
    position += sizeof(command);
    return command;
  }

  BufferWriteCommand CommandStream::readBufferWrite(const void **data) {
    BufferWriteCommand command = *reinterpret_cast<const BufferWriteCommand*>(buffer+position);
    position += sizeof(command);
    *data = reinterpret_cast<const void*>(buffer+position);
    position += command.size;
    return command;
  }

  ClearCommand CommandStream::readClear() {
    ClearCommand command = *reinterpret_cast<const ClearCommand*>(buffer+position);
    position += sizeof(command);
    return command;
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

  RenderTargetSetCommand CommandStream::readRenderTargetSet() {
    RenderTargetSetCommand command = *reinterpret_cast<const RenderTargetSetCommand*>(buffer+position);
    position += sizeof(command);
    return command;
  }

  TextureSetCommand CommandStream::readTextureSet() {
    TextureSetCommand command = *reinterpret_cast<const TextureSetCommand*>(buffer+position);
    position += sizeof(command);
    return command;
  }

  UniformMat4SetCommand CommandStream::readUniformMat4Set(const float **data) {
    UniformMat4SetCommand command = *reinterpret_cast<const UniformMat4SetCommand*>(buffer+position);
    position += sizeof(command);
    *data = reinterpret_cast<const float*>(buffer+position);
    position += command.count*sizeof(float)*16;
    return command;
  }
}
