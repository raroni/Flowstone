#include <stddef.h>
#include "Rendering/Backend/Functions.h"
#include "Rendering/Backend/UniformHandle.h"
#include "Rendering/ProgramName.h"
#include "Rendering/Uniforms.h"
#include "Rendering/Programs.h"

namespace Rendering {
  namespace Uniforms {
    List list;

    void initialize() {
      Backend::ProgramHandle boneProgram = Programs::handles[static_cast<size_t>(ProgramName::Bone)];
      list.boneJointWorldTransformation = Backend::getUniform(boneProgram, "jointWorldTransformation");
      list.boneModelJointTransformation = Backend::getUniform(boneProgram, "modelJointTransformations");

      Backend::ProgramHandle staticProgram = Programs::handles[static_cast<size_t>(ProgramName::Static)];
      list.staticModelWorldTransform = Backend::getUniform(staticProgram, "modelWorldTransform");

      Backend::ProgramHandle mergeProgram = Programs::handles[static_cast<size_t>(ProgramName::Merge)];
      list.mergeDiffuse = Backend::getUniform(mergeProgram, "diffuse");
      list.mergeLambert = Backend::getUniform(mergeProgram, "lambert");
    }
  }
}
