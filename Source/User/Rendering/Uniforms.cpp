#include <stddef.h>
#include "Rendering/Backend/Functions.h"
#include "Rendering/Backend/UniformHandle.h"
#include "Rendering/Uniforms.h"
#include "Rendering/Programs.h"

namespace Rendering {
  namespace Uniforms {
    List list;

    void initialize() {
      Backend::ProgramHandle geometryBoneProgram = Programs::handles.geometryBone;
      list.geometryBoneJointWorldTransform = Backend::getUniform(geometryBoneProgram, "jointWorldTransform");
      list.geometryBoneModelJointTransform = Backend::getUniform(geometryBoneProgram, "modelJointTransforms");

      Backend::ProgramHandle geometryStaticProgram = Programs::handles.geometryStatic;
      list.geometryStaticModelWorldTransform = Backend::getUniform(geometryStaticProgram, "modelWorldTransform");

      Backend::ProgramHandle mergeProgram = Programs::handles.merge;
      list.mergeDiffuseTexture = Backend::getUniform(mergeProgram, "diffuseTexture");
      list.mergeNormalTexture = Backend::getUniform(mergeProgram, "normalTexture");
      list.mergeDepthTexture = Backend::getUniform(mergeProgram, "depthTexture");
      list.mergeShadowTexture = Backend::getUniform(mergeProgram, "shadowTexture");
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
      list.mergeInverseShadowSize = Backend::getUniform(mergeProgram, "inverseShadowSize");

      Backend::ProgramHandle shadowBone = Programs::handles.shadowBone;
      list.shadowBoneWorldClipTransform = Backend::getUniform(shadowBone, "worldClipTransform");
      list.shadowBoneJointWorldTransform = Backend::getUniform(shadowBone, "jointWorldTransform");
      list.shadowBoneModelJointTransforms = Backend::getUniform(shadowBone, "modelJointTransforms");

      Backend::ProgramHandle shadowStatic = Programs::handles.shadowStatic;
      list.shadowStaticWorldClipTransform = Backend::getUniform(shadowStatic, "worldClipTransform");
      list.shadowStaticModelWorldTransform = Backend::getUniform(shadowStatic, "modelWorldTransform");

      Backend::ProgramHandle ssaoGrain = Programs::handles.ssaoGrain;
      list.ssaoGrainNoiseTexture = Backend::getUniform(ssaoGrain, "noiseTexture");
      list.ssaoGrainNormalTexture = Backend::getUniform(ssaoGrain, "normalTexture");
      list.ssaoGrainDepthTexture = Backend::getUniform(ssaoGrain, "depthTexture");
      list.ssaoGrainWorldViewTransform = Backend::getUniform(ssaoGrain, "worldViewTransform");
      list.ssaoGrainViewClipTransform = Backend::getUniform(ssaoGrain, "viewClipTransform");
      list.ssaoGrainClipWorldTransform = Backend::getUniform(ssaoGrain, "clipWorldTransform");
      list.ssaoGrainSampleKernel = Backend::getUniform(ssaoGrain, "sampleKernel");
      list.ssaoGrainNoiseScale = Backend::getUniform(ssaoGrain, "noiseScale");
      list.ssaoGrainSampleRadius = Backend::getUniform(ssaoGrain, "sampleRadius");
      list.ssaoGrainSampleDifferenceLimit = Backend::getUniform(ssaoGrain, "sampleDifferenceLimit");

      Backend::ProgramHandle ssaoBlur = Programs::handles.ssaoBlur;
      list.ssaoBlurGrainTexture = Backend::getUniform(ssaoBlur, "grainTexture");
      list.ssaoBlurGrainTexelSize = Backend::getUniform(ssaoBlur, "grainTexelSize");
      list.ssaoBlurDepthDifferenceLimit = Backend::getUniform(ssaoBlur, "depthDifferenceLimit");
      list.ssaoBlurDepthTexture = Backend::getUniform(ssaoBlur, "depthTexture");
      list.ssaoBlurZNear = Backend::getUniform(ssaoBlur, "zFar");
      list.ssaoBlurZFar = Backend::getUniform(ssaoBlur, "zNear");

      Backend::ProgramHandle downsample = Programs::handles.downsample;
      list.downsampleDepthTexture = Backend::getUniform(downsample, "depthTexture");
      list.downsampleNormalTexture = Backend::getUniform(downsample, "normalTexture");
      list.downsampleZNear = Backend::getUniform(downsample, "zNear");
      list.downsampleZFar = Backend::getUniform(downsample, "zFar");
    }
  }
}
