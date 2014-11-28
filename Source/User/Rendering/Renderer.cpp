#include "Core/Error.h"
#include "Rendering/Renderer.h"
#include "Rendering/Programs.h"
#include "Rendering/Backend/Backend.h"
#include "Rendering/CommandType.h"

namespace Rendering {
  void Renderer::initialize() {
    Programs::initialize();
    Backend::setClearColor(0, 0, 1);
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
    Backend::clear();
    for(uint16_t i=0; stream.getCount()>i; i++) {
      CommandType type = stream.readType();
      switch(type) {
        case CommandType::ProgramSet: {
          ProgramSetCommand command = stream.readProgramSet();
          Backend::setProgram(command.program);
          break;
        }
        case CommandType::UniformMat4Set: {
          UniformMat4SetCommand command = stream.readUniformMat4Set();
          Backend::setUniformMat4(command.uniform, command.matrix.components);
          break;
        }
        case CommandType::Uniform8Mat4Set: {
          Uniform8Mat4SetCommand command = stream.readUniform8Mat4Set();
          Backend::setUniformMat4(command.uniform, command.matrices[0].components, 8);
          break;
        }
        case CommandType::ObjectSet: {
          ObjectSetCommand command = stream.readObjectSet();
          Backend::setObject(command.object);
          break;
        }
        case CommandType::IndexedDraw: {
          IndexedDrawCommand command = stream.readIndexedDraw();
          Backend::drawIndexed(command.indexCount);
          break;
        }
        default:
          fatalError("Unknown command type.");
          break;
      }
    }
  }
}
