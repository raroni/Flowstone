#ifndef RENDERING_COMMANDS_H
#define RENDERING_COMMANDS_H

#include "Rendering/Backend/ProgramHandle.h"

namespace Rendering {
  struct ProgramChangeCommand {
    Backend::ProgramHandle program;
  };
}

#endif
