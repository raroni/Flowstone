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
      Backend::UniformHandle ssaoNoise;
      Backend::UniformHandle ssaoDepth;
      Backend::UniformHandle ssaoNormal;
      Backend::UniformHandle ssaoWorldViewTransform;
      Backend::UniformHandle ssaoViewClipTransform;
      Backend::UniformHandle ssaoClipWorldTransform;
      Backend::UniformHandle ssaoSampleKernel;
      Backend::UniformHandle ssaoNoiseScale;
      Backend::UniformHandle ssaoSampleRadius;
      Backend::UniformHandle ssaoSampleDifferenceLimit;
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
      Backend::UniformHandle mergeSSAOTexelSize;
      Backend::UniformHandle mergeSSAODepthDifferenceLimit;

    };
    extern List list;

    void initialize();
  }
}

#endif
