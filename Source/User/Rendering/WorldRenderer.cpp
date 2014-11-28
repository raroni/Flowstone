#include <stddef.h>
#include <string.h>
#include "Core/Error.h"
#include "Quanta/Math/Matrix4.h"
#include "Rendering/BoneMeshInstances.h"
#include "Rendering/BoneMeshInstance.h"
#include "Rendering/Commands.h"
#include "Rendering/Programs.h"
#include "Rendering/Uniforms.h"
#include "Rendering/ProgramName.h"
#include "Rendering/UniformName.h"
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
    buildDrawQueue();
    writeDrawQueueToStream(stream);
  }

  void WorldRenderer::buildDrawQueue() {
    drawQueue.reset();
    for(uint16_t i=0; BoneMeshInstances::getCount()>i; i++) {
      BoneMeshDrawCall call;
      BoneMeshInstance &instance = BoneMeshInstances::list[i];
      BoneMesh mesh = boneMeshRegistry.get(instance.mesh);
      call.object = mesh.object;
      call.indexCount = mesh.indexCount;
      call.pose = poses[instance.transform];
      call.transform = transforms[instance.transform];
      drawQueue.addBoneMesh(call);
    }
    // add static draws here
    drawQueue.sort();
  }

  void WorldRenderer::writeDrawQueueToStream(CommandStream &stream) {
    for(uint16_t i=0; drawQueue.getCount()>i; i++) {
      const char *buffer = drawQueue.getBuffer(i);
      DrawCallType type = *reinterpret_cast<const DrawCallType*>(buffer);
      const char *drawCall = buffer+sizeof(type);
      switch(type) {
        case DrawCallType::BoneMesh: {
          const BoneMeshDrawCall *boneMeshDrawCall = reinterpret_cast<const BoneMeshDrawCall*>(drawCall);

          ProgramSetCommand programCommand;
          programCommand.program = Programs::handles[static_cast<size_t>(ProgramName::Bone)];
          stream.writeProgramSet(programCommand);

          UniformMat4SetCommand transformCommand;
          transformCommand.uniform = Uniforms::handles[static_cast<size_t>(UniformName::BoneJointWorldTransformation)];
          transformCommand.matrix = boneMeshDrawCall->transform;
          stream.writeUniformMat4Set(transformCommand);

          Uniform8Mat4SetCommand poseCommand;
          poseCommand.uniform = Uniforms::handles[static_cast<size_t>(UniformName::BoneModelJointTransformation)];
          memcpy(poseCommand.matrices, &boneMeshDrawCall->pose, sizeof(poseCommand.matrices));
          stream.writeUniform8Mat4Set(poseCommand);

          // todo: Tjek her på om objekt allerede er current
          ObjectSetCommand objectCommand;
          objectCommand.object = boneMeshDrawCall->object;
          stream.writeObjectSet(objectCommand);

          IndexedDrawCommand drawCommand;
          drawCommand.indexCount = boneMeshDrawCall->indexCount;
          stream.writeIndexedDraw(drawCommand);
          break;
        }
        default:
          fatalError("Unknown draw call type.");
          break;
      }
    }
  }
}
