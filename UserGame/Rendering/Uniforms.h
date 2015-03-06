#ifndef RENDERING_UNIFORMS_H
#define RENDERING_UNIFORMS_H

#include "SysGFX/UniformHandle.h"

namespace Rendering {
  namespace Uniforms {
    struct List {
      SysGFX::UniformHandle shadowBaseBoneWorldViewTransform;
      SysGFX::UniformHandle shadowBaseBoneViewClipTransform;
      SysGFX::UniformHandle shadowBaseBoneJointWorldTransform;
      SysGFX::UniformHandle shadowBaseBoneModelJointTransforms;
      SysGFX::UniformHandle shadowBaseStaticWorldViewTransform;
      SysGFX::UniformHandle shadowBaseStaticViewClipTransform;
      SysGFX::UniformHandle shadowBaseStaticModelWorldTransform;
      SysGFX::UniformHandle shadowBlurOffset;
      SysGFX::UniformHandle shadowBlurSourceTexture;
      SysGFX::UniformHandle geometryBoneJointWorldTransform;
      SysGFX::UniformHandle geometryBoneModelJointTransform;
      SysGFX::UniformHandle geometryStaticModelWorldTransform;
      SysGFX::UniformHandle ssaoGrainNoiseTexture;
      SysGFX::UniformHandle ssaoGrainDepthTexture;
      SysGFX::UniformHandle ssaoGrainNormalTexture;
      SysGFX::UniformHandle ssaoGrainClipWorldTransform;
      SysGFX::UniformHandle ssaoGrainSampleKernel;
      SysGFX::UniformHandle ssaoGrainNoiseScale;
      SysGFX::UniformHandle ssaoGrainSampleRadius;
      SysGFX::UniformHandle ssaoGrainSampleDifferenceLimit;
      SysGFX::UniformHandle ssaoGrainZNear;
      SysGFX::UniformHandle ssaoGrainZFar;
      SysGFX::UniformHandle ssaoBlurGrainTexture;
      SysGFX::UniformHandle ssaoBlurGrainTexelSize;
      SysGFX::UniformHandle ssaoBlurDepthDifferenceLimit;
      SysGFX::UniformHandle ssaoBlurDepthTexture;
      SysGFX::UniformHandle ssaoBlurZNear;
      SysGFX::UniformHandle ssaoBlurZFar;
      SysGFX::UniformHandle mergeAppearanceTexture;
      SysGFX::UniformHandle mergeNormalTexture;
      SysGFX::UniformHandle mergeDepthTexture;
      SysGFX::UniformHandle mergeShadowTexture;
      SysGFX::UniformHandle mergeSSAOTexture;
      SysGFX::UniformHandle mergeDownsampleScale;
      SysGFX::UniformHandle mergeCameraClipWorldTransform;
      SysGFX::UniformHandle mergeLightWorldViewTransform;
      SysGFX::UniformHandle mergeLightViewClipTransform;
      SysGFX::UniformHandle mergeInversePrimaryLightDirection;
      SysGFX::UniformHandle mergePrimaryLightColor;
      SysGFX::UniformHandle mergeInverseSecondaryLightDirection;
      SysGFX::UniformHandle mergeLowResDepthTexture;
      SysGFX::UniformHandle mergeZNear;
      SysGFX::UniformHandle mergeZFar;
      SysGFX::UniformHandle mergeInverseShadowSize;
      SysGFX::UniformHandle downsampleDepthTexture;
      SysGFX::UniformHandle downsampleNormalTexture;
      SysGFX::UniformHandle downsampleZNear;
      SysGFX::UniformHandle downsampleZFar;
      SysGFX::UniformHandle pointLightCameraClipWorldTransform;
      SysGFX::UniformHandle pointLightWorldPosition;
      SysGFX::UniformHandle pointLightRadius;
      SysGFX::UniformHandle pointLightDepthTexture;
      SysGFX::UniformHandle pointLightNormalTexture;
      SysGFX::UniformHandle pointLightResolution;
    };
    extern List list;

    void initialize();
  }
}

#endif
