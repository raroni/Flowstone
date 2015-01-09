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
      list.mergeSSAOTexture = Backend::getUniform(mergeProgram, "ssaoTexture");
      list.mergeLowResDepthTexture = Backend::getUniform(mergeProgram, "lowResDepthTexture");
      list.mergeCameraClipWorldTransform = Backend::getUniform(mergeProgram, "cameraClipWorldTransform");
      list.mergeLightWorldClipTransform = Backend::getUniform(mergeProgram, "lightWorldClipTransform");
      list.mergeInversePrimaryLightDirection = Backend::getUniform(mergeProgram, "inversePrimaryLightDirection");
      list.mergePrimaryLightColor = Backend::getUniform(mergeProgram, "primaryLightColor");
      list.mergeInverseSecondaryLightDirection = Backend::getUniform(mergeProgram, "inverseSecondaryLightDirection");
      list.mergeZNear = Backend::getUniform(mergeProgram, "zNear");
      list.mergeZFar = Backend::getUniform(mergeProgram, "zFar");
      list.mergeDownsampleScale = Backend::getUniform(mergeProgram, "downsampleScale");

      Backend::ProgramHandle shadowBone = Programs::handles[static_cast<size_t>(ProgramName::ShadowBone)];
      list.shadowBoneWorldClipTransform = Backend::getUniform(shadowBone, "worldClipTransform");
      list.shadowBoneJointWorldTransform = Backend::getUniform(shadowBone, "jointWorldTransform");
      list.shadowBoneModelJointTransforms = Backend::getUniform(shadowBone, "modelJointTransforms");

      Backend::ProgramHandle shadowStatic = Programs::handles[static_cast<size_t>(ProgramName::ShadowStatic)];
      list.shadowStaticWorldClipTransform = Backend::getUniform(shadowStatic, "worldClipTransform");
      list.shadowStaticModelWorldTransform = Backend::getUniform(shadowStatic, "modelWorldTransform");

      Backend::ProgramHandle ssaoGrain = Programs::handles[static_cast<size_t>(ProgramName::SSAOGrain)];
      list.ssaoGrainNoise = Backend::getUniform(ssaoGrain, "noise");
      list.ssaoGrainNormal = Backend::getUniform(ssaoGrain, "normal");
      list.ssaoGrainDepth = Backend::getUniform(ssaoGrain, "depth");
      list.ssaoGrainWorldViewTransform = Backend::getUniform(ssaoGrain, "worldViewTransform");
      list.ssaoGrainViewClipTransform = Backend::getUniform(ssaoGrain, "viewClipTransform");
      list.ssaoGrainClipWorldTransform = Backend::getUniform(ssaoGrain, "clipWorldTransform");
      list.ssaoGrainSampleKernel = Backend::getUniform(ssaoGrain, "sampleKernel");
      list.ssaoGrainNoiseScale = Backend::getUniform(ssaoGrain, "noiseScale");
      list.ssaoGrainSampleRadius = Backend::getUniform(ssaoGrain, "sampleRadius");
      list.ssaoGrainSampleDifferenceLimit = Backend::getUniform(ssaoGrain, "sampleDifferenceLimit");

      Backend::ProgramHandle ssaoBlur = Programs::handles[static_cast<size_t>(ProgramName::SSAOBlur)];
      list.ssaoBlurGrainTexture = Backend::getUniform(ssaoBlur, "grainTexture");
      list.ssaoBlurGrainTexelSize = Backend::getUniform(ssaoBlur, "grainTexelSize");
      list.ssaoBlurDepthDifferenceLimit = Backend::getUniform(ssaoBlur, "depthDifferenceLimit");
      list.ssaoBlurDepthTexture = Backend::getUniform(ssaoBlur, "depthTexture");
      list.ssaoBlurZNear = Backend::getUniform(ssaoBlur, "zFar");
      list.ssaoBlurZFar = Backend::getUniform(ssaoBlur, "zNear");

      Backend::ProgramHandle downsample = Programs::handles[static_cast<size_t>(ProgramName::Downsample)];
      list.downsampleDepthTexture = Backend::getUniform(downsample, "depthTexture");
      list.downsampleNormalTexture = Backend::getUniform(downsample, "normalTexture");
      list.downsampleZNear = Backend::getUniform(downsample, "zNear");
      list.downsampleZFar = Backend::getUniform(downsample, "zFar");
    }
  }
}
