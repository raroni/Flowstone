#include <string.h>
#include "Cabi/Cabi.h"
#include "Rendering/Backend/Functions.h"
#include "Rendering/Backend/ShaderType.h"
#include "Rendering/Backend/ShaderHandle.h"
#include "Rendering/Backend/ProgramHandle.h"
#include "Rendering/ProgramName.h"
#include "Rendering/Programs.h"

namespace Rendering {
  const static size_t sourceBufferLength = 4096;
  static char sourceBuffer[sourceBufferLength];

  static void loadSource(const char *filename) {
    char path[128] = "Shaders/";
    strcat(path, filename);
    cabiReadFile(path, sourceBuffer, sourceBufferLength);
  }

  static Backend::ProgramHandle initializeProgram(const char *name) {
    char pathBuffer[128];
    strcpy(pathBuffer, name);
    strcat(pathBuffer, ".vert");
    loadSource(pathBuffer);
    Backend::ShaderHandle vertexShader = Backend::createShader(Backend::ShaderType::Vertex, sourceBuffer);
    pathBuffer[strlen(name)] = '\0';
    strcat(pathBuffer, ".frag");
    loadSource(pathBuffer);
    Backend::ShaderHandle fragmentShader = Backend::createShader(Backend::ShaderType::Fragment, sourceBuffer);
    Backend::ProgramHandle program = Backend::createProgram();
    Backend::attachShader(program, vertexShader);
    Backend::attachShader(program, fragmentShader);
    Backend::linkProgram(program);
    return program;
  }

  static Backend::ProgramHandle initializeBoneProgram() {
    Backend::ProgramHandle program = initializeProgram("Bone");
    Backend::UniformBlockHandle block = Backend::getUniformBlock(program, "global");
    Backend::setUniformBlockIndex(program, block, 0);
    return program;
  }

  namespace Programs {
    Backend::ShaderHandle handles[16];

    void initialize() {
      handles[static_cast<size_t>(ProgramName::Bone)] = initializeBoneProgram();
    }
  }
}
