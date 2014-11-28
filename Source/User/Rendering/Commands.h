#ifndef RENDERING_COMMANDS_H
#define RENDERING_COMMANDS_H

#include "Quanta/Math/Matrix4.h"
#include "Rendering/Backend/UniformHandle.h"
#include "Rendering/Backend/ProgramHandle.h"
#include "Rendering/Backend/ObjectHandle.h"

namespace Rendering {
  struct ProgramSetCommand {
    Backend::ProgramHandle program;
  };

  struct ObjectSetCommand {
    Backend::ObjectHandle object;
  };

  struct UniformMat4SetCommand {
    Backend::UniformHandle uniform;
    Quanta::Matrix4 matrix;
  };

  struct Uniform8Mat4SetCommand {
    Backend::UniformHandle uniform;
    Quanta::Matrix4 matrices[8];
  };

  struct IndexedDrawCommand {
    uint16_t indexCount;
  };
}

#endif
