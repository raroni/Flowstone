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
#include "Rendering/Buffers.h"
#include "Rendering/BufferName.h"
#include "Rendering/Backend/Functions.h"
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
    writeGlobalUniformUpdate(stream);
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

  void WorldRenderer::writeGlobalUniformUpdate(CommandStream &stream) {
    Backend::BufferHandle globalBuffer = Buffers::handles[static_cast<size_t>(BufferName::Global1)];
    stream.writeBufferSet(Backend::BufferTarget::Uniform, globalBuffer);

    const size_t size = sizeof(Quanta::Matrix4)*2;
    char data[size];
    // copy the two matrices to data
    stream.writeBufferWrite(Backend::BufferTarget::Uniform, 32, data);

    stream.writeBufferSet(Backend::BufferTarget::Uniform, 0);
  }

  void WorldRenderer::writeDrawQueueToStream(CommandStream &stream) {
    for(uint16_t i=0; drawQueue.getCount()>i; i++) {
      const char *buffer = drawQueue.getBuffer(i);
      DrawCallType type = *reinterpret_cast<const DrawCallType*>(buffer);
      const char *drawCall = buffer+sizeof(type);
      switch(type) {
        case DrawCallType::BoneMesh: {
          const BoneMeshDrawCall *boneMeshDrawCall = reinterpret_cast<const BoneMeshDrawCall*>(drawCall);

          stream.writeProgramSet(Programs::handles[static_cast<size_t>(ProgramName::Bone)]);

          stream.writeUniformMat4Set(
            Uniforms::handles[static_cast<size_t>(UniformName::BoneJointWorldTransformation)],
            1,
            &boneMeshDrawCall->transform
          );

          stream.writeUniformMat4Set(
            Uniforms::handles[static_cast<size_t>(UniformName::BoneModelJointTransformation)],
            8,
            &boneMeshDrawCall->pose
          );

          // todo: Tjek her på om objekt allerede er current
          stream.writeObjectSet(boneMeshDrawCall->object);
          stream.writeIndexedDraw(boneMeshDrawCall->indexCount);
          break;
        }
        default:
          fatalError("Unknown draw call type.");
          break;
      }
    }
  }
}
