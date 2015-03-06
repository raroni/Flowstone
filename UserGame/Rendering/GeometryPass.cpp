#include <stddef.h>
#include "Common/Error.h"
#include "Rendering/DrawQueue.h"
#include "Rendering/DrawSet.h"
#include "Rendering/BoneDrawSet.h"
#include "Rendering/BoneMesh.h"
#include "Rendering/RenderTargets.h"
#include "SysGFX/ClearBit.h"
#include "Rendering/StaticMesh.h"
#include "Rendering/StaticMeshes.h"
#include "Rendering/CommandStream.h"
#include "Rendering/Programs.h"
#include "Rendering/Uniforms.h"
#include "Rendering/BoneMeshRegistry.h"
#include "Rendering/GeometryPass.h"

namespace Rendering {
  namespace GeometryPass {
    DrawQueue drawQueue;

    static void buildDrawQueue(const DrawSet &drawSet, const BoneMeshRegistry &boneMeshRegistry) {
      const BoneDrawSet &boneSet = drawSet.boneSet;
      for(uint16_t i=0; boneSet.count>i; i++) {
        BoneMeshDrawCall call;
        BoneMesh mesh = boneMeshRegistry.get(boneSet.meshes[i]);
        call.object = mesh.object;
        call.indexCount = mesh.indexCount;
        call.pose = boneSet.poses[i];
        call.transform = boneSet.transforms[i];
        drawQueue.addBoneMesh(call);
      }
      const StaticDrawSet &staticSet = drawSet.staticSet;
      for(uint16_t i=0; staticSet.count>i; i++) {
        StaticMeshDrawCall call;
        const StaticMesh& mesh = StaticMeshes::get(staticSet.meshes[i]);
        call.object = mesh.object;
        call.indexCount = mesh.indexCount;
        call.transform = staticSet.transforms[i];
        drawQueue.addStaticMesh(call);
      }
      drawQueue.sort();
    }

    void writeStream(CommandStream &stream) {
      for(uint16_t i=0; drawQueue.getCount()>i; i++) {
        const char *buffer = drawQueue.getBuffer(i);
        DrawCallType type = *reinterpret_cast<const DrawCallType*>(buffer);
        const char *drawCall = buffer+sizeof(type);
        switch(type) {
          case DrawCallType::BoneMesh: {
            const BoneMeshDrawCall *boneMeshDrawCall = reinterpret_cast<const BoneMeshDrawCall*>(drawCall);

            stream.writeProgramSet(Programs::handles.geometryBone);

            stream.writeUniformMat4Set(
              Uniforms::list.geometryBoneJointWorldTransform,
              1,
              &boneMeshDrawCall->transform.components[0]
            );

            stream.writeUniformMat4Set(
              Uniforms::list.geometryBoneModelJointTransform,
              8,
              &boneMeshDrawCall->pose.joints[0].components[0]
            );

            stream.writeObjectSet(boneMeshDrawCall->object);
            stream.writeIndexedDraw(boneMeshDrawCall->indexCount, SysGFX::DataType::UnsignedShort);
            break;
          }
          case DrawCallType::StaticMesh: {
            const StaticMeshDrawCall *staticMeshDrawCall = reinterpret_cast<const StaticMeshDrawCall*>(drawCall);
            stream.writeProgramSet(Programs::handles.geometryStatic);
            stream.writeUniformMat4Set(
              Uniforms::list.geometryStaticModelWorldTransform,
              1,
              &staticMeshDrawCall->transform.components[0]
            );
            stream.writeObjectSet(staticMeshDrawCall->object);
            stream.writeIndexedDraw(staticMeshDrawCall->indexCount, SysGFX::DataType::UnsignedShort);
            break;
          }
          default:
            fatalError("Unknown draw call type.");
            break;
        }
      }
    }

    void write(CommandStream &stream, const DrawSet &drawSet, const BoneMeshRegistry &boneMeshRegistry) {
      stream.writeRenderTargetSet(RenderTargets::handles.geometry);
      stream.writeClear(
        static_cast<SysGFX::ClearBitMask>(SysGFX::ClearBit::Color) |
        static_cast<SysGFX::ClearBitMask>(SysGFX::ClearBit::Depth)
      );
      buildDrawQueue(drawSet, boneMeshRegistry);
      writeStream(stream);
      drawQueue.reset();
    }
  }
}
