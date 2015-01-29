#ifndef RENDERING_UNIFORMS_H
#define RENDERING_UNIFORMS_H

#include "Rendering/Backend/UniformHandle.h"

namespace Rendering {
  namespace Uniforms {
    struct List {
      Backend::UniformHandle shadowBaseBoneWorldViewTransform;
      Backend::UniformHandle shadowBaseBoneViewClipTransform;
      Backend::UniformHandle shadowBaseBoneJointWorldTransform;
      Backend::UniformHandle shadowBaseBoneModelJointTransforms;
      Backend::UniformHandle shadowBaseStaticWorldViewTransform;
      Backend::UniformHandle shadowBaseStaticViewClipTransform;
      Backend::UniformHandle shadowBaseStaticModelWorldTransform;
      Backend::UniformHandle shadowBlurOffset;
      Backend::UniformHandle shadowBlurSourceTexture;
      Backend::UniformHandle geometryBoneJointWorldTransform;
      Backend::UniformHandle geometryBoneModelJointTransform;
      Backend::UniformHandle geometryStaticModelWorldTransform;
      Backend::UniformHandle ssaoGrainNoiseTexture;
      Backend::UniformHandle ssaoGrainDepthTexture;
      Backend::UniformHandle ssaoGrainNormalTexture;
      Backend::UniformHandle ssaoGrainClipWorldTransform;
      Backend::UniformHandle ssaoGrainSampleKernel;
      Backend::UniformHandle ssaoGrainNoiseScale;
      Backend::UniformHandle ssaoGrainSampleRadius;
      Backend::UniformHandle ssaoGrainSampleDifferenceLimit;
      Backend::UniformHandle ssaoGrainZNear;
      Backend::UniformHandle ssaoGrainZFar;
      Backend::UniformHandle ssaoBlurGrainTexture;
      Backend::UniformHandle ssaoBlurGrainTexelSize;
      Backend::UniformHandle ssaoBlurDepthDifferenceLimit;
      Backend::UniformHandle ssaoBlurDepthTexture;
      Backend::UniformHandle ssaoBlurZNear;
      Backend::UniformHandle ssaoBlurZFar;
      Backend::UniformHandle mergeDiffuseTexture;
      Backend::UniformHandle mergeNormalTexture;
      Backend::UniformHandle mergeDepthTexture;
      Backend::UniformHandle mergeShadowTexture;
      Backend::UniformHandle mergeSSAOTexture;
      Backend::UniformHandle mergeDownsampleScale;
      Backend::UniformHandle mergeCameraClipWorldTransform;
      Backend::UniformHandle mergeLightWorldViewTransform;
      Backend::UniformHandle mergeLightViewClipTransform;
      Backend::UniformHandle mergeInversePrimaryLightDirection;
      Backend::UniformHandle mergePrimaryLightColor;
      Backend::UniformHandle mergeInverseSecondaryLightDirection;
      Backend::UniformHandle mergeLowResDepthTexture;
      Backend::UniformHandle mergeZNear;
      Backend::UniformHandle mergeZFar;
      Backend::UniformHandle mergeInverseShadowSize;
      Backend::UniformHandle downsampleDepthTexture;
      Backend::UniformHandle downsampleNormalTexture;
      Backend::UniformHandle downsampleZNear;
      Backend::UniformHandle downsampleZFar;
      Backend::UniformHandle pointLightModelWorldTransform;
      Backend::UniformHandle pointLightCameraClipWorldTransform;
      Backend::UniformHandle pointLightDepthTexture;
      Backend::UniformHandle pointLightNormalTexture;
      Backend::UniformHandle pointLightResolution;
    };
    extern List list;

    void initialize();
  }
}

#endif
