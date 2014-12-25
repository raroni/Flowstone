#include <stddef.h>
#include "Rendering/CommandStream.h"
#include "Rendering/RenderTargets.h"
#include "Rendering/ProgramName.h"
#include "Rendering/Uniforms.h"
#include "Rendering/Backend/ClearBit.h"
#include "Rendering/Programs.h"
#include "Rendering/DrawSet.h"
#include "Rendering/BoneDrawSet.h"
#include "Rendering/StaticMesh.h"
#include "Rendering/StaticMeshes.h"
#include "Rendering/BoneMesh.h"
#include "Rendering/BoneMeshRegistry.h"
#include "Rendering/StaticDrawSet.h"
#include "Rendering/ShadowMap.h"

namespace Rendering {
  namespace ShadowMap {
    void write(CommandStream &stream, const BoneMeshRegistry &boneMeshRegistry, const DrawSet &drawSet, const Quanta::Matrix4 &lightViewClipTransform, const Quanta::Matrix4 &lightWorldViewTransform) {
      stream.writeRenderTargetSet(RenderTargets::handles.shadow);
      stream.writeClear(static_cast<Backend::ClearBitMask>(Backend::ClearBit::Depth));

      stream.writeProgramSet(Programs::handles[static_cast<size_t>(ProgramName::ShadowStatic)]);
      stream.writeUniformMat4Set(Uniforms::list.shadowStaticViewClipTransform, 1, lightViewClipTransform.components);
      stream.writeUniformMat4Set(Uniforms::list.shadowStaticWorldViewTransform, 1, lightWorldViewTransform.components);
      const StaticDrawSet &staticSet = drawSet.staticSet;
      for(uint16_t i=0; staticSet.count>i; i++) {
        const StaticMesh& mesh = StaticMeshes::get(staticSet.meshes[i]);
        stream.writeUniformMat4Set(
          Uniforms::list.shadowStaticModelWorldTransform,
          1,
          staticSet.transforms[i].components
        );
        stream.writeObjectSet(mesh.object);
        stream.writeIndexedDraw(mesh.indexCount, Backend::DataType::UnsignedShort);
      }

      stream.writeProgramSet(Programs::handles[static_cast<size_t>(ProgramName::ShadowBone)]);
      stream.writeUniformMat4Set(Uniforms::list.shadowBoneViewClipTransform, 1, lightViewClipTransform.components);
      stream.writeUniformMat4Set(Uniforms::list.shadowBoneWorldViewTransform, 1, lightWorldViewTransform.components);
      const BoneDrawSet &boneSet = drawSet.boneSet;
      for(uint16_t i=0; boneSet.count>i; i++) {
        BoneMesh mesh = boneMeshRegistry.get(boneSet.meshes[i]);

        stream.writeUniformMat4Set(
          Uniforms::list.shadowBoneJointWorldTransform,
          1,
          boneSet.transforms[i].components
        );

        stream.writeUniformMat4Set(
          Uniforms::list.shadowBoneModelJointTransforms,
          8,
          boneSet.poses[i].joints[0].components
        );

        stream.writeObjectSet(mesh.object);
        stream.writeIndexedDraw(mesh.indexCount, Backend::DataType::UnsignedShort);
      }

      stream.writeRenderTargetSet(0);
    }
  }
}
