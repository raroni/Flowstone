#include <stddef.h>
#include <string.h>
#include "Quanta/Math/Matrix4.h"
#include "Rendering/BoneMeshInstances.h"
#include "Rendering/BoneMeshInstance.h"
#include "Rendering/Commands.h"
#include "Rendering/Programs.h"
#include "Rendering/ProgramName.h"
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
    // todo update constant uniform / uniform object, world view

    ProgramSetCommand command;
    command.program = Programs::handles[static_cast<size_t>(ProgramName::Bone)];
    stream.writeProgramSet(command);

    drawQueue.reset();
    for(uint16_t i=0; BoneMeshInstances::getCount()>i; i++) {
      BoneMeshInstance &instance = BoneMeshInstances::list[i];
      BoneMeshDrawCall call;
      call.mesh = instance.mesh;
      const Quanta::Matrix4 &transform = transforms[instance.transform];
      memcpy(call.transform, &transform, sizeof(transform));
      const Pose &pose = poses[instance.transform];
      memcpy(call.pose, &pose, sizeof(pose));
      drawQueue.addBoneMesh(call);
    }
  }
}
