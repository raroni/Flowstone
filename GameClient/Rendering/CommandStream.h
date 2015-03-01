#ifndef RENDERING_COMMAND_STREAM_H
#define RENDERING_COMMAND_STREAM_H

#include "Rendering/Commands.h"
#include "Rendering/CommandType.h"
#include "Rendering/Backend/ClearBitMask.h"
#include "Rendering/Backend/RenderTargetHandle.h"

namespace Rendering {
  class CommandStream {
  public:
    void reset();
    void rewind();
    uint16_t getCount() { return count; }
    void writeBufferSet(Backend::BufferTarget target, Backend::BufferHandle buffer);
    void writeBufferWrite(Backend::BufferTarget target, uint16_t size, const void *data);
    void writeClear(Backend::ClearBitMask mask);
    void writeCullFaceSet(Backend::CullFace face);
    void writeDisableDepthTest();
    void writeEnableDepthTest();
    void writeDisableBlending();
    void writeEnableBlending();
    void writeIndexedDraw(uint16_t indexCount, Backend::DataType dataType);
    void writeBlendFunctionSet(Backend::BlendFactor sourceFactor, Backend::BlendFactor destinationFactor);
    void writeObjectSet(Backend::ObjectHandle object);
    void writeProgramSet(Backend::ProgramHandle program);
    void writeRenderTargetSet(Backend::RenderTargetHandle renderTarget);
    void writeTexturePairSet(uint8_t unit, Backend::TextureHandle handle);
    void writeTextureSet(Backend::TextureHandle handle);
    void writeTextureUnitSet(uint8_t unit);
    void writeUniformFloatSet(Backend::UniformHandle uniform, uint16_t count, const float *data);
    void writeUniformMat4Set(Backend::UniformHandle uniform, uint16_t count, const float *data);
    void writeUniformVec2Set(Backend::UniformHandle uniform, uint16_t count, const float *data);
    void writeUniformVec3Set(Backend::UniformHandle uniform, uint16_t count, const float *data);
    void writeViewportSet(uint16_t width, uint16_t height);
    CommandType readType();
    const BufferSetCommand& readBufferSet();
    const BufferWriteCommand& readBufferWrite(const void **data);
    const ClearCommand& readClear();
    const CullFaceSetCommand& readCullFaceSet();
    const IndexedDrawCommand& readIndexedDraw();
    const BlendFunctionSetCommand& readBlendFunctionSet();
    const ObjectSetCommand& readObjectSet();
    const ProgramSetCommand& readProgramSet();
    const RenderTargetSetCommand& readRenderTargetSet();
    const TexturePairSetCommand& readTexturePairSet();
    const TextureSetCommand& readTextureSet();
    const TextureUnitSetCommand& readTextureUnitSet();
    const UniformFloatSetCommand& readUniformFloatSet(const float **data);
    const UniformMat4SetCommand& readUniformMat4Set(const float **data);
    const UniformVec2SetCommand& readUniformVec2Set(const float **data);
    const UniformVec3SetCommand& readUniformVec3Set(const float **data);
    const ViewportSetCommand& readViewportSet();
  private:
    void writeType(CommandType type);
    uint16_t position = 0;
    char buffer[1024*50];
    uint16_t count = 0;
  };
}

#endif
