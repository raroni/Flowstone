#include <stddef.h>
#include "Rendering/Backend/Backend.h"
#include "Rendering/Backend/UniformHandle.h"
#include "Rendering/UniformName.h"
#include "Rendering/ProgramName.h"
#include "Rendering/Uniforms.h"
#include "Rendering/Programs.h"

namespace Rendering {
  namespace Uniforms {
    Backend::UniformHandle handles[32];

    static void setupLocation(Backend::ProgramHandle program, UniformName enumName, const char *stringName) {
      handles[static_cast<size_t>(enumName)] = Backend::getUniformLocation(program, stringName);
    }

    void initialize() {
      Backend::ProgramHandle program = Programs::handles[static_cast<size_t>(ProgramName::Bone)];
      setupLocation(program, UniformName::BoneJointWorldTransformation, "jointWorldTransformation");
      setupLocation(program, UniformName::BoneModelJointTransformation, "modelJointTransformation");
    }
  }
}
