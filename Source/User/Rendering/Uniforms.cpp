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
      list.mergeNormal = Backend::getUniform(mergeProgram, "normal");
      list.mergeDepth = Backend::getUniform(mergeProgram, "depth");
      list.mergeShadow = Backend::getUniform(mergeProgram, "shadow");
      list.mergeSSAO = Backend::getUniform(mergeProgram, "ssao");
      list.mergeCameraClipWorldTransform = Backend::getUniform(mergeProgram, "cameraClipWorldTransform");
      list.mergeLightWorldClipTransform = Backend::getUniform(mergeProgram, "lightWorldClipTransform");
      list.mergeInversePrimaryLightDirection = Backend::getUniform(mergeProgram, "inversePrimaryLightDirection");
      list.mergePrimaryLightColor = Backend::getUniform(mergeProgram, "primaryLightColor");
      list.mergeInverseSecondaryLightDirection = Backend::getUniform(mergeProgram, "inverseSecondaryLightDirection");
      list.mergeSSAOTexelSize = Backend::getUniform(mergeProgram, "ssaoTexelSize");

      Backend::ProgramHandle shadowBone = Programs::handles[static_cast<size_t>(ProgramName::ShadowBone)];
      list.shadowBoneWorldClipTransform = Backend::getUniform(shadowBone, "worldClipTransform");
      list.shadowBoneJointWorldTransform = Backend::getUniform(shadowBone, "jointWorldTransform");
      list.shadowBoneModelJointTransforms = Backend::getUniform(shadowBone, "modelJointTransforms");

      Backend::ProgramHandle shadowStatic = Programs::handles[static_cast<size_t>(ProgramName::ShadowStatic)];
      list.shadowStaticWorldClipTransform = Backend::getUniform(shadowStatic, "worldClipTransform");
      list.shadowStaticModelWorldTransform = Backend::getUniform(shadowStatic, "modelWorldTransform");

      Backend::ProgramHandle ssao = Programs::handles[static_cast<size_t>(ProgramName::SSAO)];
      list.ssaoNoise = Backend::getUniform(ssao, "noise");
      list.ssaoNormal = Backend::getUniform(ssao, "normal");
      list.ssaoDepth = Backend::getUniform(ssao, "depth");
      list.ssaoWorldViewTransform = Backend::getUniform(ssao, "worldViewTransform");
      list.ssaoViewClipTransform = Backend::getUniform(ssao, "viewClipTransform");
      list.ssaoClipWorldTransform = Backend::getUniform(ssao, "clipWorldTransform");
      list.ssaoSampleKernel = Backend::getUniform(ssao, "sampleKernel");
      list.ssaoNoiseScale = Backend::getUniform(ssao, "noiseScale");
      list.ssaoSampleRadius = Backend::getUniform(ssao, "sampleRadius");
    }
  }
}
