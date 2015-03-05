#include <string.h>
#include "Rendering/CommandStream.h"

namespace Rendering {
  void CommandStream::writeBufferSet(SysGFX::BufferTarget target, SysGFX::BufferHandle buffer) {
    writeType(CommandType::BufferSet);
    BufferSetCommand command;
    command.target = target;
    command.buffer = buffer;
    memcpy(this->buffer+position, &command, sizeof(command));
    position += sizeof(command);
  }

  void CommandStream::writeBufferWrite(SysGFX::BufferTarget target, uint16_t size, const void *data) {
    writeType(CommandType::BufferWrite);
    BufferWriteCommand command;
    command.target = target;
    command.size = size;
    memcpy(buffer+position, &command, sizeof(command));
    position += sizeof(command);
    memcpy(buffer+position, data, size);
    position += size;
  }

  void CommandStream::writeClear(SysGFX::ClearBitMask mask) {
    writeType(CommandType::Clear);
    ClearCommand command;
    command.mask = mask;
    memcpy(buffer+position, &command, sizeof(command));
    position += sizeof(command);
  }

  void CommandStream::writeCullFaceSet(SysGFX::CullFace face) {
    writeType(CommandType::CullFaceSet);
    CullFaceSetCommand command;
    command.face = face;
    memcpy(buffer+position, &command, sizeof(command));
    position += sizeof(command);
  }

  void CommandStream::writeDisableDepthTest() {
    writeType(CommandType::DisableDepthTest);
  }

  void CommandStream::writeEnableDepthTest() {
    writeType(CommandType::EnableDepthTest);
  }

  void CommandStream::writeDisableBlending() {
    writeType(CommandType::DisableBlending);
  }

  void CommandStream::writeEnableBlending() {
    writeType(CommandType::EnableBlending);
  }

  void CommandStream::writeIndexedDraw(uint16_t indexCount, SysGFX::DataType dataType) {
    writeType(CommandType::IndexedDraw);
    IndexedDrawCommand command;
    command.indexCount = indexCount;
    command.dataType = dataType;
    memcpy(buffer+position, &command, sizeof(command));
    position += sizeof(command);
  }

  void CommandStream::writeBlendFunctionSet(SysGFX::BlendFactor sourceFactor, SysGFX::BlendFactor destinationFactor) {
    writeType(CommandType::BlendFunctionSet);
    BlendFunctionSetCommand command;
    command.sourceFactor = sourceFactor;
    command.destinationFactor = sourceFactor;
    memcpy(buffer+position, &command, sizeof(command));
    position += sizeof(command);
  }

  void CommandStream::writeObjectSet(SysGFX::ObjectHandle object) {
    writeType(CommandType::ObjectSet);
    ObjectSetCommand command;
    command.object = object;
    memcpy(buffer+position, &command, sizeof(command));
    position += sizeof(command);
  }

  void CommandStream::writeProgramSet(SysGFX::ProgramHandle program) {
    writeType(CommandType::ProgramSet);
    ProgramSetCommand command;
    command.program = program;
    memcpy(buffer+position, &command, sizeof(command));
    position += sizeof(command);
  }

  void CommandStream::writeRenderTargetSet(SysGFX::RenderTargetHandle renderTarget) {
    writeType(CommandType::RenderTargetSet);
    RenderTargetSetCommand command;
    command.renderTarget = renderTarget;
    memcpy(buffer+position, &command, sizeof(command));
    position += sizeof(command);
  }

  void CommandStream::writeTexturePairSet(uint8_t unit, SysGFX::TextureHandle handle) {
    writeType(CommandType::TexturePairSet);
    TexturePairSetCommand command;
    command.unit = unit;
    command.handle = handle;
    memcpy(buffer+position, &command, sizeof(command));
    position += sizeof(command);
  }

  void CommandStream::writeTextureSet(SysGFX::TextureHandle handle) {
    writeType(CommandType::TextureSet);
    TextureSetCommand command;
    command.handle = handle;
    memcpy(buffer+position, &command, sizeof(command));
    position += sizeof(command);
  }

  void CommandStream::writeTextureUnitSet(uint8_t unit) {
    writeType(CommandType::TextureUnitSet);
    TextureUnitSetCommand command;
    command.unit = unit;
    memcpy(buffer+position, &command, sizeof(command));
    position += sizeof(command);
  }

  void CommandStream::writeUniformFloatSet(SysGFX::UniformHandle uniform, uint16_t count, const float *data) {
    writeType(CommandType::UniformFloatSet);
    UniformFloatSetCommand command;
    command.uniform = uniform;
    command.count = count;
    memcpy(buffer+position, &command, sizeof(command));
    position += sizeof(command);
    size_t dataSize = count*sizeof(float);
    memcpy(buffer+position, data, dataSize);
    position += dataSize;
  }

  void CommandStream::writeUniformMat4Set(SysGFX::UniformHandle uniform, uint16_t count, const float *data) {
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

  void CommandStream::writeUniformVec2Set(SysGFX::UniformHandle uniform, uint16_t count, const float *data) {
    writeType(CommandType::UniformVec2Set);
    UniformVec2SetCommand command;
    command.uniform = uniform;
    command.count = count;
    memcpy(buffer+position, &command, sizeof(command));
    position += sizeof(command);
    size_t dataSize = count*sizeof(float)*2;
    memcpy(buffer+position, data, dataSize);
    position += dataSize;
  }

  void CommandStream::writeUniformVec3Set(SysGFX::UniformHandle uniform, uint16_t count, const float *data) {
    writeType(CommandType::UniformVec3Set);
    UniformVec3SetCommand command;
    command.uniform = uniform;
    command.count = count;
    memcpy(buffer+position, &command, sizeof(command));
    position += sizeof(command);
    size_t dataSize = count*sizeof(float)*3;
    memcpy(buffer+position, data, dataSize);
    position += dataSize;
  }

  void CommandStream::writeViewportSet(uint16_t width, uint16_t height) {
    writeType(CommandType::ViewportSet);
    ViewportSetCommand command;
    command.width = width;
    command.height = height;
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

  const BufferSetCommand& CommandStream::readBufferSet() {
    const BufferSetCommand &command = *reinterpret_cast<const BufferSetCommand*>(buffer+position);
    position += sizeof(command);
    return command;
  }

  const BufferWriteCommand& CommandStream::readBufferWrite(const void **data) {
    const BufferWriteCommand &command = *reinterpret_cast<const BufferWriteCommand*>(buffer+position);
    position += sizeof(command);
    *data = reinterpret_cast<const void*>(buffer+position);
    position += command.size;
    return command;
  }

  const ClearCommand& CommandStream::readClear() {
    const ClearCommand &command = *reinterpret_cast<const ClearCommand*>(buffer+position);
    position += sizeof(command);
    return command;
  }

  const CullFaceSetCommand& CommandStream::readCullFaceSet() {
    const CullFaceSetCommand &command = *reinterpret_cast<const CullFaceSetCommand*>(buffer+position);
    position += sizeof(command);
    return command;
  }

  const IndexedDrawCommand& CommandStream::readIndexedDraw() {
    const IndexedDrawCommand& command = *reinterpret_cast<const IndexedDrawCommand*>(buffer+position);
    position += sizeof(command);
    return command;
  }

  const BlendFunctionSetCommand& CommandStream::readBlendFunctionSet() {
    const BlendFunctionSetCommand &command = *reinterpret_cast<const BlendFunctionSetCommand*>(buffer+position);
    position += sizeof(command);
    return command;
  }

  const ObjectSetCommand& CommandStream::readObjectSet() {
    const ObjectSetCommand &command = *reinterpret_cast<const ObjectSetCommand*>(buffer+position);
    position += sizeof(command);
    return command;
  }

  const ProgramSetCommand& CommandStream::readProgramSet() {
    const ProgramSetCommand &command = *reinterpret_cast<const ProgramSetCommand*>(buffer+position);
    position += sizeof(command);
    return command;
  }

  const RenderTargetSetCommand& CommandStream::readRenderTargetSet() {
    const RenderTargetSetCommand &command = *reinterpret_cast<const RenderTargetSetCommand*>(buffer+position);
    position += sizeof(command);
    return command;
  }

  const TexturePairSetCommand& CommandStream::readTexturePairSet() {
    const TexturePairSetCommand &command = *reinterpret_cast<const TexturePairSetCommand*>(buffer+position);
    position += sizeof(command);
    return command;
  }

  const TextureSetCommand& CommandStream::readTextureSet() {
    const TextureSetCommand &command = *reinterpret_cast<const TextureSetCommand*>(buffer+position);
    position += sizeof(command);
    return command;
  }

  const TextureUnitSetCommand& CommandStream::readTextureUnitSet() {
    const TextureUnitSetCommand &command = *reinterpret_cast<const TextureUnitSetCommand*>(buffer+position);
    position += sizeof(command);
    return command;
  }

  const UniformFloatSetCommand& CommandStream::readUniformFloatSet(const float **data) {
    const UniformFloatSetCommand &command = *reinterpret_cast<const UniformFloatSetCommand*>(buffer+position);
    position += sizeof(command);
    *data = reinterpret_cast<const float*>(buffer+position);
    position += command.count*sizeof(float);
    return command;
  }

  const UniformMat4SetCommand& CommandStream::readUniformMat4Set(const float **data) {
    const UniformMat4SetCommand &command = *reinterpret_cast<const UniformMat4SetCommand*>(buffer+position);
    position += sizeof(command);
    *data = reinterpret_cast<const float*>(buffer+position);
    position += command.count*sizeof(float)*16;
    return command;
  }

  const UniformVec2SetCommand& CommandStream::readUniformVec2Set(const float **data) {
    const UniformVec2SetCommand &command = *reinterpret_cast<const UniformVec2SetCommand*>(buffer+position);
    position += sizeof(command);
    *data = reinterpret_cast<const float*>(buffer+position);
    position += command.count*sizeof(float)*2;
    return command;
  }

  const UniformVec3SetCommand& CommandStream::readUniformVec3Set(const float **data) {
    const UniformVec3SetCommand &command = *reinterpret_cast<const UniformVec3SetCommand*>(buffer+position);
    position += sizeof(command);
    *data = reinterpret_cast<const float*>(buffer+position);
    position += command.count*sizeof(float)*3;
    return command;
  }

  const ViewportSetCommand& CommandStream::readViewportSet() {
    const ViewportSetCommand &command = *reinterpret_cast<const ViewportSetCommand*>(buffer+position);
    position += sizeof(command);
    return command;
  }
}
