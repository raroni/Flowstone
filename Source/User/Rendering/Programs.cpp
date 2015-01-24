#include <string.h>
#include "Cabi/Cabi.h"
#include "Rendering/Backend/Functions.h"
#include "Rendering/Backend/ShaderType.h"
#include "Rendering/Backend/ShaderHandle.h"
#include "Rendering/Backend/ProgramHandle.h"
#include "Rendering/Programs.h"

namespace Rendering {
  const static size_t sourceBufferLength = 4096;
  static char sourceBuffer[sourceBufferLength];

  static void loadSource(const char *filename) {
    char path[128] = "Shaders/";
    strcat(path, filename);
    cabiReadFile(path, sourceBuffer, sourceBufferLength);
  }

  static Backend::ProgramHandle initializeStandardProgram(const char *name) {
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

  static Backend::ProgramHandle initializeShadowBaseBoneProgram() {
    Backend::ProgramHandle program = Backend::createProgram();
    loadSource("ShadowBaseBone.vert");
    Backend::ShaderHandle vertexShader = Backend::createShader(Backend::ShaderType::Vertex, sourceBuffer);
    Backend::attachShader(program, vertexShader);
    loadSource("ShadowBase.frag");
    Backend::ShaderHandle fragmentShader = Backend::createShader(Backend::ShaderType::Fragment, sourceBuffer);
    Backend::attachShader(program, fragmentShader);
    Backend::linkProgram(program);
    return program;
  }

  static Backend::ProgramHandle initializeShadowBaseStaticProgram() {
    Backend::ProgramHandle program = Backend::createProgram();
    loadSource("ShadowBaseStatic.vert");
    Backend::ShaderHandle vertexShader = Backend::createShader(Backend::ShaderType::Vertex, sourceBuffer);
    Backend::attachShader(program, vertexShader);
    loadSource("ShadowBase.frag");
    Backend::ShaderHandle fragmentShader = Backend::createShader(Backend::ShaderType::Fragment, sourceBuffer);
    Backend::attachShader(program, fragmentShader);
    Backend::linkProgram(program);
    return program;
  }

  static Backend::ProgramHandle initializeGeometryProgram(const char *name) {
    Backend::ProgramHandle program = initializeStandardProgram(name);
    Backend::UniformBlockHandle block = Backend::getUniformBlock(program, "global");
    Backend::setUniformBlockIndex(program, block, 0);
    return program;
  }

  static Backend::ProgramHandle initializeFullscreenQuadProgram(const char *fragmentShaderName) {
    Backend::ProgramHandle program = Backend::createProgram();
    loadSource("FullscreenQuad.vert");
    Backend::ShaderHandle vertexShader = Backend::createShader(Backend::ShaderType::Vertex, sourceBuffer);
    Backend::attachShader(program, vertexShader);

    char fragmentPathBuffer[128];
    strcpy(fragmentPathBuffer, fragmentShaderName);
    strcat(fragmentPathBuffer, ".frag");
    loadSource(fragmentPathBuffer);
    Backend::ShaderHandle fragmentShader = Backend::createShader(Backend::ShaderType::Fragment, sourceBuffer);
    Backend::attachShader(program, fragmentShader);

    Backend::linkProgram(program);
    return program;
  }

  namespace Programs {
    HandleList handles;

    void initialize() {
      handles.geometryBone = initializeGeometryProgram("GeometryBone");
      handles.geometryStatic = initializeGeometryProgram("GeometryStatic");
      handles.merge = initializeStandardProgram("Merge");
      handles.shadowBaseBone = initializeShadowBaseBoneProgram();
      handles.shadowBaseStatic = initializeShadowBaseStaticProgram();
      handles.ssaoGrain = initializeStandardProgram("SSAOGrain");
      handles.ssaoBlur = initializeStandardProgram("SSAOBlur");
      handles.downsample = initializeStandardProgram("Downsample");
      handles.shadowBlur = initializeFullscreenQuadProgram("ShadowBlur");
    }
  }
}
