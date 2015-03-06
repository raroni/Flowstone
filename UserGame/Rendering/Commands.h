#ifndef RENDERING_COMMANDS_H
#define RENDERING_COMMANDS_H

#include "SysGFX/BufferHandle.h"
#include "SysGFX/BufferTarget.h"
#include "SysGFX/DataType.h"
#include "SysGFX/ObjectHandle.h"
#include "SysGFX/TextureHandle.h"
#include "SysGFX/ProgramHandle.h"
#include "SysGFX/UniformHandle.h"
#include "SysGFX/ClearBitMask.h"
#include "SysGFX/CullFace.h"
#include "SysGFX/BlendFactor.h"
#include "SysGFX/RenderTargetHandle.h"

namespace Rendering {
  struct ProgramSetCommand {
    SysGFX::ProgramHandle program;
  };

  struct ObjectSetCommand {
    SysGFX::ObjectHandle object;
  };

  struct UniformFloatSetCommand {
    SysGFX::UniformHandle uniform;
    uint16_t count;
  };

  struct UniformMat4SetCommand {
    SysGFX::UniformHandle uniform;
    uint16_t count;
  };

  struct UniformVec2SetCommand {
    SysGFX::UniformHandle uniform;
    uint16_t count;
  };

  struct UniformVec3SetCommand {
    SysGFX::UniformHandle uniform;
    uint16_t count;
  };

  struct IndexedDrawCommand {
    uint16_t indexCount;
    SysGFX::DataType dataType;
  };

  struct BufferSetCommand {
    SysGFX::BufferTarget target;
    SysGFX::BufferHandle buffer;
  };

  struct BufferWriteCommand {
    uint16_t size;
    SysGFX::BufferTarget target;
  };

  struct RenderTargetSetCommand {
    SysGFX::RenderTargetHandle renderTarget;
  };

  struct ClearCommand {
    SysGFX::ClearBitMask mask;
  };

  struct ViewportSetCommand {
    uint16_t width;
    uint16_t height;
  };

  struct CullFaceSetCommand {
    SysGFX::CullFace face;
  };

  struct TexturePairSetCommand {
    uint8_t unit;
    SysGFX::TextureHandle handle;
  };

  struct TextureSetCommand {
    SysGFX::TextureHandle handle;
  };

  struct TextureUnitSetCommand {
    uint8_t unit;
  };

  struct BlendFunctionSetCommand {
    SysGFX::BlendFactor sourceFactor;
    SysGFX::BlendFactor destinationFactor;
  };
}

#endif
