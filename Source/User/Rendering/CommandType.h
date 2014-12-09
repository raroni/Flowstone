#ifndef RENDERING_COMMAND_TYPE_H
#define RENDERING_COMMAND_TYPE_H

namespace Rendering {
  enum class CommandType {
    ProgramSet,
    UniformMat4Set,
    UniformVec3Set,
    ObjectSet,
    IndexedDraw,
    BufferSet,
    BufferWrite,
    RenderTargetSet,
    TextureSet,
    EnableDepthTest,
    DisableDepthTest,
    Clear,
    ViewportSet
  };
}

#endif
