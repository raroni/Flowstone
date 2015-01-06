#ifndef RENDERING_PROGRAM_NAME_H
#define RENDERING_PROGRAM_NAME_H

namespace Rendering {
  enum class ProgramName {
    GeometryBone,
    GeometryStatic,
    Merge,
    ShadowBone,
    ShadowStatic,
    SSAOGrain,
    SSAOBlur,
    Downsample
  };
}

#endif
