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
      Backend::UniformHandle ssaoGrainNoise;
      Backend::UniformHandle ssaoGrainDepth;
      Backend::UniformHandle ssaoGrainNormal;
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
      Backend::UniformHandle mergeDiffuse;
      Backend::UniformHandle mergeNormal;
      Backend::UniformHandle mergeDepth;
      Backend::UniformHandle mergeShadow;
      Backend::UniformHandle mergeSSAO;
      Backend::UniformHandle mergeCameraClipWorldTransform;
      Backend::UniformHandle mergeLightWorldClipTransform;
      Backend::UniformHandle mergeInversePrimaryLightDirection;
      Backend::UniformHandle mergePrimaryLightColor;
      Backend::UniformHandle mergeInverseSecondaryLightDirection;
      Backend::UniformHandle downsampleDepthTexture;
      Backend::UniformHandle downsampleNormalTexture;
    };
    extern List list;

    void initialize();
  }
}

#endif
