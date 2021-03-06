#ifndef RENDERING_COMMAND_TYPE_H
#define RENDERING_COMMAND_TYPE_H

namespace Rendering {
  enum class CommandType {
    ProgramSet,
    UniformFloatSet,
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
    EnableBlending,
    DisableBlending,
    Clear,
    ViewportSet,
    CullFaceSet,
    TexturePairSet,
    TextureSet,
    TextureUnitSet,
    BlendFunctionSet
  };
}

#endif
