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
      list.mergeAppearanceTexture = Backend::getUniform(mergeProgram, "appearanceTexture");
      list.mergeNormalTexture = Backend::getUniform(mergeProgram, "normalTexture");
      list.mergeDepthTexture = Backend::getUniform(mergeProgram, "depthTexture");
      list.mergeShadowTexture = Backend::getUniform(mergeProgram, "shadowTexture");
      list.mergeSSAOTexture = Backend::getUniform(mergeProgram, "ssaoTexture");
      list.mergeLowResDepthTexture = Backend::getUniform(mergeProgram, "lowResDepthTexture");
      list.mergeCameraClipWorldTransform = Backend::getUniform(mergeProgram, "cameraClipWorldTransform");
      list.mergeLightWorldViewTransform = Backend::getUniform(mergeProgram, "lightWorldViewTransform");
      list.mergeLightViewClipTransform = Backend::getUniform(mergeProgram, "lightViewClipTransform");
      list.mergeInversePrimaryLightDirection = Backend::getUniform(mergeProgram, "inversePrimaryLightDirection");
      list.mergePrimaryLightColor = Backend::getUniform(mergeProgram, "primaryLightColor");
      list.mergeInverseSecondaryLightDirection = Backend::getUniform(mergeProgram, "inverseSecondaryLightDirection");
      list.mergeZNear = Backend::getUniform(mergeProgram, "zNear");
      list.mergeZFar = Backend::getUniform(mergeProgram, "zFar");
      list.mergeDownsampleScale = Backend::getUniform(mergeProgram, "downsampleScale");
      list.mergeInverseShadowSize = Backend::getUniform(mergeProgram, "inverseShadowSize");

      Backend::ProgramHandle shadowBaseBone = Programs::handles.shadowBaseBone;
      list.shadowBaseBoneWorldViewTransform = Backend::getUniform(shadowBaseBone, "worldViewTransform");
      list.shadowBaseBoneViewClipTransform = Backend::getUniform(shadowBaseBone, "viewClipTransform");
      list.shadowBaseBoneJointWorldTransform = Backend::getUniform(shadowBaseBone, "jointWorldTransform");
      list.shadowBaseBoneModelJointTransforms = Backend::getUniform(shadowBaseBone, "modelJointTransforms");

      Backend::ProgramHandle shadowBaseStatic = Programs::handles.shadowBaseStatic;
      list.shadowBaseStaticWorldViewTransform = Backend::getUniform(shadowBaseStatic, "worldViewTransform");
      list.shadowBaseStaticViewClipTransform = Backend::getUniform(shadowBaseStatic, "viewClipTransform");
      list.shadowBaseStaticModelWorldTransform = Backend::getUniform(shadowBaseStatic, "modelWorldTransform");

      Backend::ProgramHandle shadowBlur = Programs::handles.shadowBlur;
      list.shadowBlurOffset = Backend::getUniform(shadowBlur, "offset");
      list.shadowBlurSourceTexture = Backend::getUniform(shadowBlur, "sourceTexture");

      Backend::ProgramHandle ssaoGrain = Programs::handles.ssaoGrain;
      list.ssaoGrainNoiseTexture = Backend::getUniform(ssaoGrain, "noiseTexture");
      list.ssaoGrainNormalTexture = Backend::getUniform(ssaoGrain, "normalTexture");
      list.ssaoGrainDepthTexture = Backend::getUniform(ssaoGrain, "depthTexture");
      list.ssaoGrainClipWorldTransform = Backend::getUniform(ssaoGrain, "clipWorldTransform");
      list.ssaoGrainSampleKernel = Backend::getUniform(ssaoGrain, "sampleKernel");
      list.ssaoGrainNoiseScale = Backend::getUniform(ssaoGrain, "noiseScale");
      list.ssaoGrainSampleRadius = Backend::getUniform(ssaoGrain, "sampleRadius");
      list.ssaoGrainSampleDifferenceLimit = Backend::getUniform(ssaoGrain, "sampleDifferenceLimit");
      list.ssaoGrainZNear = Backend::getUniform(ssaoGrain, "zNear");
      list.ssaoGrainZFar = Backend::getUniform(ssaoGrain, "zFar");

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

      Backend::ProgramHandle pointLight = Programs::handles.pointLight;
      list.pointLightRadius = Backend::getUniform(pointLight, "radius");
      list.pointLightWorldPosition = Backend::getUniform(pointLight, "worldPosition");
      list.pointLightCameraClipWorldTransform = Backend::getUniform(pointLight, "cameraClipWorldTransform");
      list.pointLightDepthTexture = Backend::getUniform(pointLight, "depthTexture");
      list.pointLightNormalTexture = Backend::getUniform(pointLight, "normalTexture");
      list.pointLightResolution = Backend::getUniform(pointLight, "resolution");
    }
  }
}
