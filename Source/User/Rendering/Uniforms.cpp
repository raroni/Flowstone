#include <stddef.h>
#include "Rendering/Backend/Functions.h"
#include "Rendering/Backend/UniformHandle.h"
#include "Rendering/UniformName.h"
#include "Rendering/ProgramName.h"
#include "Rendering/Uniforms.h"
#include "Rendering/Programs.h"

namespace Rendering {
  namespace Uniforms {
    Backend::UniformHandle handles[32];

    static void setupLocation(Backend::ProgramHandle program, UniformName enumName, const char *stringName) {
      handles[static_cast<size_t>(enumName)] = Backend::getUniform(program, stringName);
    }

    void initialize() {
      Backend::ProgramHandle boneProgram = Programs::handles[static_cast<size_t>(ProgramName::Bone)];
      setupLocation(boneProgram, UniformName::BoneJointWorldTransformation, "jointWorldTransformation");
      setupLocation(boneProgram, UniformName::BoneModelJointTransformation, "modelJointTransformations");

      Backend::ProgramHandle mergeProgram = Programs::handles[static_cast<size_t>(ProgramName::Merge)];
      setupLocation(mergeProgram, UniformName::MergeDiffuse, "diffuse");
      setupLocation(mergeProgram, UniformName::MergeLambert, "lambert");
    }
  }
}
