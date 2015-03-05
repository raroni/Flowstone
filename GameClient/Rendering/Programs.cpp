#include <string.h>
#include "SysFile/SysFile.h"
#include "SysGFX/SysGFX.h"
#include "SysGFX/ShaderType.h"
#include "SysGFX/ShaderHandle.h"
#include "SysGFX/ProgramHandle.h"
#include "Rendering/Programs.h"

namespace Rendering {
  const static size_t sourceBufferLength = 4096;
  static char sourceBuffer[sourceBufferLength];

  static void loadSource(const char *filename) {
    char path[128] = "Shaders/";
    strcat(path, filename);
    SysFile::readFile(path, sourceBuffer, sourceBufferLength);
  }

  static SysGFX::ProgramHandle initializeStandardProgram(const char *name) {
    char pathBuffer[128];
    strcpy(pathBuffer, name);
    strcat(pathBuffer, ".vert");
    loadSource(pathBuffer);
    SysGFX::ShaderHandle vertexShader = SysGFX::createShader(SysGFX::ShaderType::Vertex, sourceBuffer);
    pathBuffer[strlen(name)] = '\0';
    strcat(pathBuffer, ".frag");
    loadSource(pathBuffer);
    SysGFX::ShaderHandle fragmentShader = SysGFX::createShader(SysGFX::ShaderType::Fragment, sourceBuffer);
    SysGFX::ProgramHandle program = SysGFX::createProgram();
    SysGFX::attachShader(program, vertexShader);
    SysGFX::attachShader(program, fragmentShader);
    SysGFX::linkProgram(program);
    return program;
  }

  static SysGFX::ProgramHandle initializeShadowBaseBoneProgram() {
    SysGFX::ProgramHandle program = SysGFX::createProgram();
    loadSource("ShadowBaseBone.vert");
    SysGFX::ShaderHandle vertexShader = SysGFX::createShader(SysGFX::ShaderType::Vertex, sourceBuffer);
    SysGFX::attachShader(program, vertexShader);
    loadSource("ShadowBase.frag");
    SysGFX::ShaderHandle fragmentShader = SysGFX::createShader(SysGFX::ShaderType::Fragment, sourceBuffer);
    SysGFX::attachShader(program, fragmentShader);
    SysGFX::linkProgram(program);
    return program;
  }

  static SysGFX::ProgramHandle initializeShadowBaseStaticProgram() {
    SysGFX::ProgramHandle program = SysGFX::createProgram();
    loadSource("ShadowBaseStatic.vert");
    SysGFX::ShaderHandle vertexShader = SysGFX::createShader(SysGFX::ShaderType::Vertex, sourceBuffer);
    SysGFX::attachShader(program, vertexShader);
    loadSource("ShadowBase.frag");
    SysGFX::ShaderHandle fragmentShader = SysGFX::createShader(SysGFX::ShaderType::Fragment, sourceBuffer);
    SysGFX::attachShader(program, fragmentShader);
    SysGFX::linkProgram(program);
    return program;
  }

  static void attachCameraTransformsBlock(SysGFX::ProgramHandle program) {
    SysGFX::UniformBlockHandle block = SysGFX::getUniformBlock(program, "CameraTransforms");
    SysGFX::setUniformBlockIndex(program, block, 0);
  }

  static SysGFX::ProgramHandle initializeCameraTransformBlockProgram(const char *name) {
    SysGFX::ProgramHandle program = initializeStandardProgram(name);
    attachCameraTransformsBlock(program);
    return program;
  }

  static SysGFX::ProgramHandle initializeFullscreenQuadProgram(const char *fragmentShaderName) {
    SysGFX::ProgramHandle program = SysGFX::createProgram();
    loadSource("FullscreenQuad.vert");
    SysGFX::ShaderHandle vertexShader = SysGFX::createShader(SysGFX::ShaderType::Vertex, sourceBuffer);
    SysGFX::attachShader(program, vertexShader);

    char fragmentPathBuffer[128];
    strcpy(fragmentPathBuffer, fragmentShaderName);
    strcat(fragmentPathBuffer, ".frag");
    loadSource(fragmentPathBuffer);
    SysGFX::ShaderHandle fragmentShader = SysGFX::createShader(SysGFX::ShaderType::Fragment, sourceBuffer);
    SysGFX::attachShader(program, fragmentShader);

    SysGFX::linkProgram(program);
    return program;
  }

  static SysGFX::ProgramHandle initializeSSAOGrain() {
    SysGFX::ProgramHandle program = initializeFullscreenQuadProgram("SSAOGrain");
    attachCameraTransformsBlock(program);
    return program;
  }

  static SysGFX::ProgramHandle initializeGeometryProgram(const char *type) {
    SysGFX::ProgramHandle program = SysGFX::createProgram();

    char vertexPathBuffer[128] = "Geometry";
    strcat(vertexPathBuffer, type);
    strcat(vertexPathBuffer, ".vert");
    loadSource(vertexPathBuffer);
    SysGFX::ShaderHandle vertexShader = SysGFX::createShader(SysGFX::ShaderType::Vertex, sourceBuffer);
    SysGFX::attachShader(program, vertexShader);

    loadSource("Geometry.frag");
    SysGFX::ShaderHandle fragmentShader = SysGFX::createShader(SysGFX::ShaderType::Fragment, sourceBuffer);
    SysGFX::attachShader(program, fragmentShader);

    SysGFX::linkProgram(program);

    attachCameraTransformsBlock(program);

    return program;
  }

  namespace Programs {
    HandleList handles;

    void initialize() {
      handles.geometryBone = initializeGeometryProgram("Bone");
      handles.geometryStatic = initializeGeometryProgram("Static");
      handles.merge = initializeFullscreenQuadProgram("Merge");
      handles.pointLight = initializeCameraTransformBlockProgram("PointLight");
      handles.shadowBaseBone = initializeShadowBaseBoneProgram();
      handles.shadowBaseStatic = initializeShadowBaseStaticProgram();
      handles.ssaoGrain = initializeSSAOGrain();;
      handles.ssaoBlur = initializeFullscreenQuadProgram("SSAOBlur");
      handles.downsample = initializeFullscreenQuadProgram("Downsample");
      handles.shadowBlur = initializeFullscreenQuadProgram("ShadowBlur");
    }
  }
}
