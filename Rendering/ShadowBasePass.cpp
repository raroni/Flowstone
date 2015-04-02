#include <stddef.h>
#include "Rendering/CommandStream.h"
#include "Rendering/RenderTargets.h"
#include "Rendering/Uniforms.h"
#include "SysGFX/ClearBit.h"
#include "SysGFX/CullFace.h"
#include "Rendering/Programs.h"
#include "Rendering/DrawSet.h"
#include "Rendering/BoneDrawSet.h"
#include "Rendering/StaticMesh.h"
#include "Rendering/StaticMeshes.h"
#include "Rendering/BoneMesh.h"
#include "Rendering/BoneMeshRegistry.h"
#include "Rendering/StaticDrawSet.h"
#include "Rendering/ShadowBasePass.h"

namespace Rendering {
  namespace ShadowBasePass {
    void write(
      CommandStream &stream,
      const BoneMeshRegistry &boneMeshRegistry,
      const DrawSet &drawSet,
      const Quanta::Matrix4 &lightWorldViewTransform,
      const Quanta::Matrix4 &lightViewClipTransform
    ) {
      stream.writeRenderTargetSet(RenderTargets::handles.shadowBase);
      stream.writeClear(
        static_cast<SysGFX::ClearBitMask>(SysGFX::ClearBit::Depth) |
        static_cast<SysGFX::ClearBitMask>(SysGFX::ClearBit::Color)
      );

      stream.writeProgramSet(Programs::handles.shadowBaseStatic);
      stream.writeUniformMat4Set(Uniforms::list.shadowBaseStaticWorldViewTransform, 1, lightWorldViewTransform.components);
      stream.writeUniformMat4Set(Uniforms::list.shadowBaseStaticViewClipTransform, 1, lightViewClipTransform.components);
      const StaticDrawSet &staticSet = drawSet.staticSet;
      for(uint16_t i=0; staticSet.count>i; i++) {
        const StaticMesh& mesh = StaticMeshes::get(staticSet.meshes[i]);
        stream.writeUniformMat4Set(
          Uniforms::list.shadowBaseStaticModelWorldTransform,
          1,
          staticSet.transforms[i].components
        );
        stream.writeObjectSet(mesh.object);
        stream.writeIndexedDraw(mesh.indexCount, SysGFX::DataType::UnsignedShort);
      }

      stream.writeProgramSet(Programs::handles.shadowBaseBone);
      stream.writeUniformMat4Set(Uniforms::list.shadowBaseBoneWorldViewTransform, 1, lightWorldViewTransform.components);
      stream.writeUniformMat4Set(Uniforms::list.shadowBaseBoneViewClipTransform, 1, lightViewClipTransform.components);
      const BoneDrawSet &boneSet = drawSet.boneSet;
      for(uint16_t i=0; boneSet.count>i; i++) {
        BoneMesh mesh = boneMeshRegistry.get(boneSet.meshes[i]);

        stream.writeUniformMat4Set(
          Uniforms::list.shadowBaseBoneJointWorldTransform,
          1,
          boneSet.transforms[i].components
        );

        stream.writeUniformMat4Set(
          Uniforms::list.shadowBaseBoneModelJointTransforms,
          8,
          boneSet.poses[i].joints[0].components
        );

        stream.writeObjectSet(mesh.object);
        stream.writeIndexedDraw(mesh.indexCount, SysGFX::DataType::UnsignedShort);
      }

      stream.writeRenderTargetSet(0);
    }
  }
}
