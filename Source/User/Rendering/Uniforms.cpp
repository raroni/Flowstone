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
      Backend::ProgramHandle geometryBoneProgram = Programs::handles[static_cast<size_t>(ProgramName::GeometryBone)];
      list.geometryBoneJointWorldTransform = Backend::getUniform(geometryBoneProgram, "jointWorldTransform");
      list.geometryBoneModelJointTransform = Backend::getUniform(geometryBoneProgram, "modelJointTransforms");

      Backend::ProgramHandle geometryStaticProgram = Programs::handles[static_cast<size_t>(ProgramName::GeometryStatic)];
      list.geometryStaticModelWorldTransform = Backend::getUniform(geometryStaticProgram, "modelWorldTransform");

      Backend::ProgramHandle mergeProgram = Programs::handles[static_cast<size_t>(ProgramName::Merge)];
      list.mergeDiffuse = Backend::getUniform(mergeProgram, "diffuse");
      list.mergeLambert = Backend::getUniform(mergeProgram, "lambert");
    }
  }
}
