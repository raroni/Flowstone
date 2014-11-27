#ifndef RENDERING_BACKEND_OPENGL_H
#define RENDERING_BACKEND_OPENGL_H

#include "Rendering/Backend/ObjectHandle.h"
#include "Rendering/Backend/BoneVertex.h"
#include "Rendering/Backend/ShaderType.h"
#include "Rendering/Backend/ShaderHandle.h"
#include "Rendering/Backend/ProgramHandle.h"

namespace Rendering {
  namespace Backend {
    namespace OpenGL {
      ObjectHandle createBoneMesh(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount);
      ShaderHandle createShader(ShaderType type, const char *source);
      ProgramHandle createProgram();
      void linkProgram(ProgramHandle handle);
      void attachShader(ProgramHandle program, ShaderHandle shader);
      void changeProgram(ProgramHandle program);
    }
  }
}

#endif
