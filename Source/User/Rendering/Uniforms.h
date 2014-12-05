#ifndef RENDERING_UNIFORMS_H
#define RENDERING_UNIFORMS_H

#include "Rendering/Backend/UniformHandle.h"

namespace Rendering {
  namespace Uniforms {
    struct List {
      Backend::UniformHandle boneJointWorldTransform;
      Backend::UniformHandle boneModelJointTransform;
      Backend::UniformHandle staticModelWorldTransform;
      Backend::UniformHandle mergeDiffuse;
      Backend::UniformHandle mergeLambert;
    };
    extern List list;

    void initialize();
  }
}

#endif
