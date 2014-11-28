#ifndef RENDERING_COMMANDS_H
#define RENDERING_COMMANDS_H

#include "Rendering/Backend/BufferHandle.h"
#include "Rendering/Backend/BufferTarget.h"
#include "Rendering/Backend/ObjectHandle.h"
#include "Rendering/Backend/ProgramHandle.h"
#include "Rendering/Backend/UniformHandle.h"

namespace Rendering {
  struct ProgramSetCommand {
    Backend::ProgramHandle program;
  };

  struct ObjectSetCommand {
    Backend::ObjectHandle object;
  };

  struct UniformMat4SetCommand {
    Backend::UniformHandle uniform;
    uint16_t count;
  };

  struct IndexedDrawCommand {
    uint16_t indexCount;
  };

  struct BufferSetCommand {
    Backend::BufferTarget target;
    Backend::BufferHandle buffer;
  };

  struct BufferWriteCommand {
    uint16_t size;
    Backend::BufferTarget target;
  };
}

#endif
