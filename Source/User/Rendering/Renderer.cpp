#include "Core/Error.h"
#include "Rendering/Renderer.h"
#include "Rendering/Programs.h"
#include "Rendering/Backend/Backend.h"
#include "Rendering/CommandType.h"

namespace Rendering {
  void Renderer::initialize() {
    Programs::initialize();
  }

  BoneMeshIndex Renderer::createBoneMesh(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount) {
    return worldRenderer.createBoneMesh(vertices, vertexCount, indices, indexCount);
  }

  void Renderer::createBoneMeshInstance(BoneMeshIndex meshIndex, TransformIndex transformIndex) {
    worldRenderer.createBoneMeshInstance(meshIndex, transformIndex);
  }

  void Renderer::draw() {
    worldRenderer.writeCommands(stream);
    // uiRenderer.writeCommands(stream);
    stream.rewind();
    dispatch();
    stream.reset();
  }

  void Renderer::setTransforms(const Quanta::Matrix4 *transforms) {
    worldRenderer.transforms = transforms;
  }

  void Renderer::setPoses(const Pose *poses) {
    worldRenderer.poses = poses;
  }

  void Renderer::dispatch() {
    for(uint16_t i=0; stream.getCount()>i; i++) {
      CommandType type = stream.readType();
      switch(type) {
        case CommandType::ProgramSet: {
          ProgramSetCommand command = stream.readProgramSet();
          Backend::setProgram(command.program);
          break;
        }
        default:
          fatalError("Unknown command type.");
          break;
      }
    }
  }
}
