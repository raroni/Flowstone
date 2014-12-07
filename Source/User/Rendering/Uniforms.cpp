#include <stddef.h>
#include "Rendering/Backend/Functions.h"
#include "Rendering/Backend/UniformHandle.h"
#include "Rendering/ProgramName.h"
#include "Rendering/Uniforms.h"
#include "Rendering/Programs.h"

namespace Rendering {
  namespace Uniforms {
    List list;

    void initialize() {
      Backend::ProgramHandle geometryBoneProgram = Programs::handles[static_cast<size_t>(ProgramName::GeometryBone)];
      list.geometryBoneJointWorldTransform = Backend::getUniform(geometryBoneProgram, "jointWorldTransform");
      list.geometryBoneModelJointTransform = Backend::getUniform(geometryBoneProgram, "modelJointTransforms");

      Backend::ProgramHandle geometryStaticProgram = Programs::handles[static_cast<size_t>(ProgramName::GeometryStatic)];
      list.geometryStaticModelWorldTransform = Backend::getUniform(geometryStaticProgram, "modelWorldTransform");

      Backend::ProgramHandle mergeProgram = Programs::handles[static_cast<size_t>(ProgramName::Merge)];
      list.mergeDiffuse = Backend::getUniform(mergeProgram, "diffuse");
      list.mergeLambert = Backend::getUniform(mergeProgram, "lambert");
      list.mergeDepth = Backend::getUniform(mergeProgram, "depth");
      list.mergeShadow = Backend::getUniform(mergeProgram, "shadow");
      list.mergeGeometryClipWorldTransform = Backend::getUniform(mergeProgram, "geometryClipWorldTransform");
      list.mergeLightWorldClipTransform = Backend::getUniform(mergeProgram, "lightWorldClipTransform");

      Backend::ProgramHandle shadowBone = Programs::handles[static_cast<size_t>(ProgramName::ShadowBone)];
      list.shadowBoneViewClipTransform = Backend::getUniform(shadowBone, "viewClipTransform");
      list.shadowBoneWorldViewTransform = Backend::getUniform(shadowBone, "worldViewTransform");
      list.shadowBoneJointWorldTransform = Backend::getUniform(shadowBone, "jointWorldTransform");
      list.shadowBoneModelJointTransforms = Backend::getUniform(shadowBone, "modelJointTransforms");

      Backend::ProgramHandle shadowStatic = Programs::handles[static_cast<size_t>(ProgramName::ShadowStatic)];
      list.shadowStaticViewClipTransform = Backend::getUniform(shadowStatic, "viewClipTransform");
      list.shadowStaticWorldViewTransform = Backend::getUniform(shadowStatic, "worldViewTransform");
      list.shadowStaticModelWorldTransform = Backend::getUniform(shadowStatic, "modelWorldTransform");
    }
  }
}
