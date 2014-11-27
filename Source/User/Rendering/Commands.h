#ifndef RENDERING_COMMANDS_H
#define RENDERING_COMMANDS_H

#include "Rendering/Backend/UniformHandle.h"
#include "Rendering/Backend/ProgramHandle.h"

namespace Rendering {
  struct ProgramSetCommand {
    Backend::ProgramHandle program;
  };

  struct SetUniformMat4Command {
    Backend::UniformHandle uniform;
    float data[16];
  };

  struct SetUniform8xMat4Command {
    Backend::UniformHandle uniform;
    float matrix[128];
  };
}

#endif
