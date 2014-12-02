#ifndef RENDERING_BACKEND_H
#define RENDERING_BACKEND_H

#include "Rendering/Backend/ObjectHandle.h"
#include "Rendering/Backend/ShaderType.h"
#include "Rendering/Backend/ShaderHandle.h"
#include "Rendering/Backend/UniformHandle.h"
#include "Rendering/Backend/AttributeLocation.h"
#include "Rendering/Backend/ProgramHandle.h"
#include "Rendering/Backend/ClearBitMask.h"
#include "Rendering/Backend/UniformBlockHandle.h"
#include "Rendering/Backend/BufferHandle.h"
#include "Rendering/Backend/RenderTargetHandle.h"
#include "Rendering/Backend/RenderBufferHandle.h"
#include "Rendering/Backend/BufferTarget.h"
#include "Rendering/Backend/TextureHandle.h"
#include "Rendering/Backend/DataType.h"
#include "Rendering/Backend/TextureFormat.h"

namespace Rendering {
  namespace Backend {
    ShaderHandle createShader(ShaderType type, const char *source);
    ProgramHandle createProgram();
    void linkProgram(ProgramHandle handle);
    void attachShader(ProgramHandle program, ShaderHandle shader);
    void setProgram(ProgramHandle program);
    UniformHandle getUniform(ProgramHandle program, const char *name);
    UniformBlockHandle getUniformBlock(ProgramHandle program, const char *name);
    void clear(ClearBitMask mask);
    void setClearColor(float r, float g, float b);
    void setUniformMat4(UniformHandle uniform, uint8_t count, const float *data);
    ObjectHandle createObject();
    void enableAttributeLocation(AttributeLocation location);
    void configureAttribute(AttributeLocation location, uint8_t count, Backend::DataType dataType, uint8_t stride, uint8_t offset);
    void setObject(ObjectHandle object);
    void drawIndexed(uint16_t indexCount, DataType dataType);
    BufferHandle createBuffer();
    void setBuffer(BufferTarget target, BufferHandle buffer);
    void setBufferIndex(BufferTarget target, BufferHandle buffer, uint8_t index);
    void setUniformBlockIndex(ProgramHandle program, UniformBlockHandle block, uint8_t index);
    void writeBuffer(BufferTarget target, uint16_t size, const void *data);
    RenderTargetHandle createRenderTarget();
    void setRenderTarget(RenderTargetHandle renderTarget);
    void setRenderBuffer(RenderBufferHandle renderBuffer);
    TextureHandle createTexture(uint16_t width, uint16_t height, TextureFormat format);
    void attachTexture(TextureHandle texture, uint8_t location);
    void attachRenderBuffer(RenderBufferHandle renderBuffer);
    bool checkRenderTarget();
    void setDrawBufferCount(uint8_t count);
    void setTexture(UniformHandle uniform, TextureHandle texture, uint8_t unit);
    void enableDepthTest();
    void disableDepthTest();
    RenderBufferHandle createRenderBuffer(uint16_t width, uint16_t height);
  }
}

#endif
