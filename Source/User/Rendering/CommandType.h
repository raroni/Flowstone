#ifndef RENDERING_COMMAND_TYPE_H
#define RENDERING_COMMAND_TYPE_H

namespace Rendering {
  enum class CommandType {
    ProgramSet,
    UniformMat4Set,
    UniformVec2Set,
    UniformVec3Set,
    ObjectSet,
    IndexedDraw,
    BufferSet,
    BufferWrite,
    RenderTargetSet,
    EnableDepthTest,
    DisableDepthTest,
    Clear,
    ViewportSet,
    CullFaceSet,
    TexturePairSet,
    TextureSet,
    TextureUnitSet
  };
}

#endif
