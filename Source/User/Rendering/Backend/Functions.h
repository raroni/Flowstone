#ifndef RENDERING_BACKEND_H
#define RENDERING_BACKEND_H

#include "Rendering/Backend/ObjectHandle.h"
#include "Rendering/Backend/BoneVertex.h"
#include "Rendering/Backend/ShaderType.h"
#include "Rendering/Backend/ShaderHandle.h"
#include "Rendering/Backend/UniformHandle.h"
#include "Rendering/Backend/ProgramHandle.h"
#include "Rendering/Backend/UniformBlockHandle.h"
#include "Rendering/Backend/BufferHandle.h"
#include "Rendering/Backend/BufferTarget.h"

namespace Rendering {
  namespace Backend {
    ObjectHandle createBoneMesh(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount);
    ShaderHandle createShader(ShaderType type, const char *source);
    ProgramHandle createProgram();
    void linkProgram(ProgramHandle handle);
    void attachShader(ProgramHandle program, ShaderHandle shader);
    void setProgram(ProgramHandle program);
    UniformHandle getUniform(ProgramHandle program, const char *name);
    UniformBlockHandle getUniformBlock(ProgramHandle program, const char *name);
    void clear();
    void setClearColor(float r, float g, float b);
    void setUniformMat4(UniformHandle uniform, uint8_t count, const float *data);
    void setObject(ObjectHandle object);
    void drawIndexed(uint16_t indexCount);
    BufferHandle createBuffer();
    void setBuffer(BufferTarget target, BufferHandle buffer);
    void setBufferIndex(BufferTarget target, BufferHandle buffer, uint8_t index);
    void setUniformBlockIndex(ProgramHandle program, UniformBlockHandle block, uint8_t index);
    void writeBuffer(BufferTarget target, uint16_t size, const void *data);
  }
}

#endif
