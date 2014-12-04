#include <stddef.h>
#include <string.h>
#include <math.h>
#include "Quanta/ProjectionFactory.h"
#include "Core/Error.h"
#include "Quanta/Math/Matrix4.h"
#include "Rendering/BoneMeshInstances.h"
#include "Rendering/BoneMeshInstance.h"
#include "Rendering/Commands.h"
#include "Rendering/StaticMeshes.h"
#include "Rendering/StaticMeshInstances.h"
#include "Rendering/Programs.h"
#include "Rendering/Uniforms.h"
#include "Rendering/FullscreenQuad.h"
#include "Rendering/Textures.h"
#include "Rendering/RenderTargets.h"
#include "Rendering/ProgramName.h"
#include "Rendering/Backend/ClearBit.h"
#include "Rendering/Buffers.h"
#include "Rendering/BufferName.h"
#include "Rendering/Backend/Functions.h"
#include "Rendering/CommandStream.h"
#include "Rendering/WorldRenderer.h"

namespace Rendering {
  BoneMeshIndex WorldRenderer::createBoneMesh(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount) {
    return boneMeshRegistry.create(vertices, vertexCount, indices, indexCount);
  }

  void WorldRenderer::createBoneMeshInstance(BoneMeshIndex meshIndex, TransformIndex transformIndex, Animation::PoseIndex pose) {
    BoneMeshInstances::create(meshIndex, transformIndex, pose);
  }

  StaticMeshIndex WorldRenderer::createStaticMesh(const StaticVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount) {
    return StaticMeshes::create(vertices, vertexCount, indices, indexCount);
  }

  void WorldRenderer::createStaticMeshInstance(StaticMeshIndex mesh) {
    StaticMeshInstances::create(mesh);
    return;
  }

  void WorldRenderer::updateResolution(uint16_t width, uint16_t height) {
    resolution.width = width;
    resolution.height = height;
  }

  void WorldRenderer::writeCommands(CommandStream &stream) {
    stream.writeRenderTargetSet(RenderTargets::handles.geometry);

    writeGlobalUniformUpdate(stream);
    stream.writeClear(
      static_cast<Backend::ClearBitMask>(Backend::ClearBit::Color) |
      static_cast<Backend::ClearBitMask>(Backend::ClearBit::Depth)
    );
    buildDrawQueue();
    stream.writeEnableDepthTest();
    writeDrawQueueToStream(stream);
    stream.writeDisableDepthTest();

    stream.writeRenderTargetSet(0);

    stream.writeClear(static_cast<Backend::ClearBitMask>(Backend::ClearBit::Color));
    writeMerge(stream);
  }

  void WorldRenderer::writeMerge(CommandStream &stream) {
    stream.writeProgramSet(Programs::handles[static_cast<size_t>(ProgramName::Merge)]);

    stream.writeTextureSet(
      Uniforms::list.mergeDiffuse,
      Textures::list.geometryDiffuse,
      0
    );
    stream.writeTextureSet(
      Uniforms::list.mergeLambert,
      Textures::list.geometryLambert,
      1
    );

    stream.writeObjectSet(FullscreenQuad::object);
    stream.writeIndexedDraw(6, Backend::DataType::UnsignedByte);
    stream.writeObjectSet(0);
  }

  void WorldRenderer::buildDrawQueue() {
    drawQueue.reset();
    for(uint16_t i=0; BoneMeshInstances::getCount()>i; i++) {
      BoneMeshDrawCall call;
      BoneMeshInstance &instance = BoneMeshInstances::list[i];
      BoneMesh mesh = boneMeshRegistry.get(instance.mesh);
      call.object = mesh.object;
      call.indexCount = mesh.indexCount;
      call.pose = poses[instance.pose];
      call.transform = transforms[instance.transform];
      drawQueue.addBoneMesh(call);
    }
    // add static draws here
    drawQueue.sort();
  }

  void WorldRenderer::writeGlobalUniformUpdate(CommandStream &stream) {
    Backend::BufferHandle globalBuffer = Buffers::handles[static_cast<size_t>(BufferName::Global1)];
    stream.writeBufferSet(Backend::BufferTarget::Uniform, globalBuffer);

    float aspectRatio = static_cast<float>(resolution.width)/(resolution.height);
    float fieldOfView = M_PI/3.0f;
    Quanta::Matrix4 viewClipTransform = Quanta::ProjectionFactory::perspective(fieldOfView, aspectRatio, 0.1, 50);
    Quanta::Matrix4 worldViewTransform = cameraTransform.getInverseMatrix();

    const size_t size = sizeof(Quanta::Matrix4);
    char data[size*2];
    memcpy(data, &viewClipTransform, size);
    memcpy(data+size, &worldViewTransform, size);
    stream.writeBufferWrite(Backend::BufferTarget::Uniform, size*2, data);

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
            Uniforms::list.boneJointWorldTransformation,
            1,
            &boneMeshDrawCall->transform.components[0]
          );

          stream.writeUniformMat4Set(
            Uniforms::list.boneModelJointTransformation,
            8,
            &boneMeshDrawCall->pose.joints[0].components[0]
          );

          // todo: Tjek her på om objekt allerede er current
          stream.writeObjectSet(boneMeshDrawCall->object);
          stream.writeIndexedDraw(boneMeshDrawCall->indexCount, Backend::DataType::UnsignedShort);
          break;
        }
        default:
          fatalError("Unknown draw call type.");
          break;
      }
    }
  }
}
