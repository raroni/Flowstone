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
    void writeDisableDepthTest();
    void writeEnableDepthTest();
    void writeIndexedDraw(uint16_t indexCount, Backend::DataType dataType);
    void writeObjectSet(Backend::ObjectHandle object);
    void writeProgramSet(Backend::ProgramHandle program);
    void writeRenderTargetSet(Backend::RenderTargetHandle renderTarget);
    void writeTextureSet(Backend::UniformHandle uniform, Backend::TextureHandle texture, uint8_t unit);
    void writeUniformMat4Set(Backend::UniformHandle uniform, uint16_t count, const float *data);
    CommandType readType();
    BufferSetCommand readBufferSet();
    BufferWriteCommand readBufferWrite(const void **data);
    ClearCommand readClear();
    IndexedDrawCommand readIndexedDraw();
    ObjectSetCommand readObjectSet();
    ProgramSetCommand readProgramSet();
    RenderTargetSetCommand readRenderTargetSet();
    TextureSetCommand readTextureSet();
    UniformMat4SetCommand readUniformMat4Set(const float **data);
  private:
    void writeType(CommandType type);
    uint16_t position = 0;
    char buffer[1024*50];
    uint16_t count = 0;
  };
}

#endif
