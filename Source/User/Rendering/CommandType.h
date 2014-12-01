#ifndef RENDERING_COMMAND_TYPE_H
#define RENDERING_COMMAND_TYPE_H

namespace Rendering {
  enum class CommandType {
    ProgramSet,
    UniformMat4Set,
    ObjectSet,
    IndexedDraw,
    BufferSet,
    BufferWrite,
    RenderTargetSet,
    TextureSet
  };
}

#endif
