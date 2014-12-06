#ifndef RENDERING_UNIFORMS_H
#define RENDERING_UNIFORMS_H

#include "Rendering/Backend/UniformHandle.h"

namespace Rendering {
  namespace Uniforms {
    struct List {
      Backend::UniformHandle shadowBoneViewClipTransform;
      Backend::UniformHandle shadowBoneWorldViewTransform;
      Backend::UniformHandle shadowBoneJointWorldTransform;
      Backend::UniformHandle shadowBoneModelJointTransforms;
      Backend::UniformHandle shadowStaticViewClipTransform;
      Backend::UniformHandle shadowStaticWorldViewTransform;
      Backend::UniformHandle shadowStaticModelWorldTransform;
      Backend::UniformHandle geometryBoneJointWorldTransform;
      Backend::UniformHandle geometryBoneModelJointTransform;
      Backend::UniformHandle geometryStaticModelWorldTransform;
      Backend::UniformHandle mergeDiffuse;
      Backend::UniformHandle mergeLambert;
      Backend::UniformHandle mergeShadow;
    };
    extern List list;

    void initialize();
  }
}

#endif
