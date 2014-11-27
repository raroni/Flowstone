#include <stddef.h>
#include "Rendering/BoneMeshInstances.h"
#include "Rendering/Commands.h"
#include "Rendering/ShaderPrograms.h"
#include "Rendering/ShaderProgramName.h"
#include "Rendering/CommandStream.h"
#include "Rendering/WorldRenderer.h"

namespace Rendering {
  BoneMeshIndex WorldRenderer::createBoneMesh(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount) {
    return boneMeshRegistry.create(vertices, vertexCount, indices, indexCount);
  }

  void WorldRenderer::createBoneMeshInstance(BoneMeshIndex meshIndex, TransformIndex transformIndex) {
    BoneMeshInstances::create(meshIndex, transformIndex);
  }

  void WorldRenderer::writeCommands(CommandStream &stream) {
    /*
    ProgramChangeCommand command;
    command.program = ShaderPrograms::handles[static_cast<size_t>(ShaderProgramName::Bone)];
    stream.writeProgramChange(command);
    */
  }
}
