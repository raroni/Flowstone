#include <stddef.h>
#include "SysGFX/SysGFX.h"
#include "SysGFX/UniformHandle.h"
#include "Rendering/Uniforms.h"
#include "Rendering/Programs.h"

namespace Rendering {
  namespace Uniforms {
    List list;

    void initialize() {
      SysGFX::ProgramHandle geometryBoneProgram = Programs::handles.geometryBone;
      list.geometryBoneJointWorldTransform = SysGFX::getUniform(geometryBoneProgram, "jointWorldTransform");
      list.geometryBoneModelJointTransform = SysGFX::getUniform(geometryBoneProgram, "modelJointTransforms");

      SysGFX::ProgramHandle geometryStaticProgram = Programs::handles.geometryStatic;
      list.geometryStaticModelWorldTransform = SysGFX::getUniform(geometryStaticProgram, "modelWorldTransform");

      SysGFX::ProgramHandle mergeProgram = Programs::handles.merge;
      list.mergeAppearanceTexture = SysGFX::getUniform(mergeProgram, "appearanceTexture");
      list.mergeNormalTexture = SysGFX::getUniform(mergeProgram, "normalTexture");
      list.mergeDepthTexture = SysGFX::getUniform(mergeProgram, "depthTexture");
      list.mergeShadowTexture = SysGFX::getUniform(mergeProgram, "shadowTexture");
      list.mergeSSAOTexture = SysGFX::getUniform(mergeProgram, "ssaoTexture");
      list.mergeLowResDepthTexture = SysGFX::getUniform(mergeProgram, "lowResDepthTexture");
      list.mergeCameraClipWorldTransform = SysGFX::getUniform(mergeProgram, "cameraClipWorldTransform");
      list.mergeLightWorldViewTransform = SysGFX::getUniform(mergeProgram, "lightWorldViewTransform");
      list.mergeLightViewClipTransform = SysGFX::getUniform(mergeProgram, "lightViewClipTransform");
      list.mergeInversePrimaryLightDirection = SysGFX::getUniform(mergeProgram, "inversePrimaryLightDirection");
      list.mergePrimaryLightColor = SysGFX::getUniform(mergeProgram, "primaryLightColor");
      list.mergeInverseSecondaryLightDirection = SysGFX::getUniform(mergeProgram, "inverseSecondaryLightDirection");
      list.mergeZNear = SysGFX::getUniform(mergeProgram, "zNear");
      list.mergeZFar = SysGFX::getUniform(mergeProgram, "zFar");
      list.mergeDownsampleScale = SysGFX::getUniform(mergeProgram, "downsampleScale");
      list.mergeInverseShadowSize = SysGFX::getUniform(mergeProgram, "inverseShadowSize");

      SysGFX::ProgramHandle shadowBaseBone = Programs::handles.shadowBaseBone;
      list.shadowBaseBoneWorldViewTransform = SysGFX::getUniform(shadowBaseBone, "worldViewTransform");
      list.shadowBaseBoneViewClipTransform = SysGFX::getUniform(shadowBaseBone, "viewClipTransform");
      list.shadowBaseBoneJointWorldTransform = SysGFX::getUniform(shadowBaseBone, "jointWorldTransform");
      list.shadowBaseBoneModelJointTransforms = SysGFX::getUniform(shadowBaseBone, "modelJointTransforms");

      SysGFX::ProgramHandle shadowBaseStatic = Programs::handles.shadowBaseStatic;
      list.shadowBaseStaticWorldViewTransform = SysGFX::getUniform(shadowBaseStatic, "worldViewTransform");
      list.shadowBaseStaticViewClipTransform = SysGFX::getUniform(shadowBaseStatic, "viewClipTransform");
      list.shadowBaseStaticModelWorldTransform = SysGFX::getUniform(shadowBaseStatic, "modelWorldTransform");

      SysGFX::ProgramHandle shadowBlur = Programs::handles.shadowBlur;
      list.shadowBlurOffset = SysGFX::getUniform(shadowBlur, "offset");
      list.shadowBlurSourceTexture = SysGFX::getUniform(shadowBlur, "sourceTexture");

      SysGFX::ProgramHandle ssaoGrain = Programs::handles.ssaoGrain;
      list.ssaoGrainNoiseTexture = SysGFX::getUniform(ssaoGrain, "noiseTexture");
      list.ssaoGrainNormalTexture = SysGFX::getUniform(ssaoGrain, "normalTexture");
      list.ssaoGrainDepthTexture = SysGFX::getUniform(ssaoGrain, "depthTexture");
      list.ssaoGrainClipWorldTransform = SysGFX::getUniform(ssaoGrain, "clipWorldTransform");
      list.ssaoGrainSampleKernel = SysGFX::getUniform(ssaoGrain, "sampleKernel");
      list.ssaoGrainNoiseScale = SysGFX::getUniform(ssaoGrain, "noiseScale");
      list.ssaoGrainSampleRadius = SysGFX::getUniform(ssaoGrain, "sampleRadius");
      list.ssaoGrainSampleDifferenceLimit = SysGFX::getUniform(ssaoGrain, "sampleDifferenceLimit");
      list.ssaoGrainZNear = SysGFX::getUniform(ssaoGrain, "zNear");
      list.ssaoGrainZFar = SysGFX::getUniform(ssaoGrain, "zFar");

      SysGFX::ProgramHandle ssaoBlur = Programs::handles.ssaoBlur;
      list.ssaoBlurGrainTexture = SysGFX::getUniform(ssaoBlur, "grainTexture");
      list.ssaoBlurGrainTexelSize = SysGFX::getUniform(ssaoBlur, "grainTexelSize");
      list.ssaoBlurDepthDifferenceLimit = SysGFX::getUniform(ssaoBlur, "depthDifferenceLimit");
      list.ssaoBlurDepthTexture = SysGFX::getUniform(ssaoBlur, "depthTexture");
      list.ssaoBlurZNear = SysGFX::getUniform(ssaoBlur, "zFar");
      list.ssaoBlurZFar = SysGFX::getUniform(ssaoBlur, "zNear");

      SysGFX::ProgramHandle downsample = Programs::handles.downsample;
      list.downsampleDepthTexture = SysGFX::getUniform(downsample, "depthTexture");
      list.downsampleNormalTexture = SysGFX::getUniform(downsample, "normalTexture");
      list.downsampleZNear = SysGFX::getUniform(downsample, "zNear");
      list.downsampleZFar = SysGFX::getUniform(downsample, "zFar");

      SysGFX::ProgramHandle pointLight = Programs::handles.pointLight;
      list.pointLightRadius = SysGFX::getUniform(pointLight, "radius");
      list.pointLightWorldPosition = SysGFX::getUniform(pointLight, "worldPosition");
      list.pointLightCameraClipWorldTransform = SysGFX::getUniform(pointLight, "cameraClipWorldTransform");
      list.pointLightDepthTexture = SysGFX::getUniform(pointLight, "depthTexture");
      list.pointLightNormalTexture = SysGFX::getUniform(pointLight, "normalTexture");
      list.pointLightResolution = SysGFX::getUniform(pointLight, "resolution");
    }
  }
}
