#include "Backend/Backend.h"
#include "Rendering/Uniforms.h"

namespace Rendering {
  namespace Uniforms {
    UniformHandle handles[32];

    static void setupLocation(UniformName enumName, const char *stringName) {
      handles[static_cast<size_t>(enumName)] = Backend::getUniformLocation(stringName);
    }

    void initialize() {
      Backend::setProgram(Programs::handles[static_cast<size_t>](ShaderName::Bone));
      setupLocation(UniformName::BoneJointWorldTransformation, "jointWorldTransformation");
      setupLocation(UniformName::BoneModelJointTransformation, "modelJointTransformation");
    }
  }
}
