#ifndef RENDERING_UNIFORMS_H
#define RENDERING_UNIFORMS_H

#include "Rendering/Backend/UniformHandle.h"

namespace Rendering {
  namespace Uniforms {
    struct List {
      Backend::UniformHandle shadowBoneWorldClipTransform;
      Backend::UniformHandle shadowBoneJointWorldTransform;
      Backend::UniformHandle shadowBoneModelJointTransforms;
      Backend::UniformHandle shadowStaticWorldClipTransform;
      Backend::UniformHandle shadowStaticModelWorldTransform;
      Backend::UniformHandle geometryBoneJointWorldTransform;
      Backend::UniformHandle geometryBoneModelJointTransform;
      Backend::UniformHandle geometryStaticModelWorldTransform;
      Backend::UniformHandle ssaoGrainNoiseTexture;
      Backend::UniformHandle ssaoGrainDepthTexture;
      Backend::UniformHandle ssaoGrainNormalTexture;
      Backend::UniformHandle ssaoGrainWorldViewTransform;
      Backend::UniformHandle ssaoGrainViewClipTransform;
      Backend::UniformHandle ssaoGrainClipWorldTransform;
      Backend::UniformHandle ssaoGrainSampleKernel;
      Backend::UniformHandle ssaoGrainNoiseScale;
      Backend::UniformHandle ssaoGrainSampleRadius;
      Backend::UniformHandle ssaoGrainSampleDifferenceLimit;
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
      Backend::UniformHandle mergeLightWorldClipTransform;
      Backend::UniformHandle mergeInversePrimaryLightDirection;
      Backend::UniformHandle mergePrimaryLightColor;
      Backend::UniformHandle mergeInverseSecondaryLightDirection;
      Backend::UniformHandle mergeLowResDepthTexture;
      Backend::UniformHandle mergeZNear;
      Backend::UniformHandle mergeZFar;
      Backend::UniformHandle downsampleDepthTexture;
      Backend::UniformHandle downsampleNormalTexture;
      Backend::UniformHandle downsampleZNear;
      Backend::UniformHandle downsampleZFar;
    };
    extern List list;

    void initialize();
  }
}

#endif
