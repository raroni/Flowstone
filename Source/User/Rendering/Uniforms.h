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
      Backend::UniformHandle mergeDiffuse;
      Backend::UniformHandle mergeLambert;
      Backend::UniformHandle mergeNormal;
      Backend::UniformHandle mergeDepth;
      Backend::UniformHandle mergeShadow;
      Backend::UniformHandle mergeGeometryClipWorldTransform;
      Backend::UniformHandle mergeLightWorldClipTransform;
      Backend::UniformHandle mergeLightDirection;
      Backend::UniformHandle mergeAtmosphereColor;
    };
    extern List list;

    void initialize();
  }
}

#endif
