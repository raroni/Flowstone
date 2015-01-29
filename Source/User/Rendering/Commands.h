#ifndef RENDERING_COMMANDS_H
#define RENDERING_COMMANDS_H

#include "Rendering/Backend/BufferHandle.h"
#include "Rendering/Backend/BufferTarget.h"
#include "Rendering/Backend/DataType.h"
#include "Rendering/Backend/ObjectHandle.h"
#include "Rendering/Backend/TextureHandle.h"
#include "Rendering/Backend/ProgramHandle.h"
#include "Rendering/Backend/UniformHandle.h"
#include "Rendering/Backend/ClearBitMask.h"
#include "Rendering/Backend/CullFace.h"
#include "Rendering/Backend/BlendFactor.h"
#include "Rendering/Backend/RenderTargetHandle.h"

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

  struct UniformVec2SetCommand {
    Backend::UniformHandle uniform;
    uint16_t count;
  };

  struct UniformVec3SetCommand {
    Backend::UniformHandle uniform;
    uint16_t count;
  };

  struct IndexedDrawCommand {
    uint16_t indexCount;
    Backend::DataType dataType;
  };

  struct BufferSetCommand {
    Backend::BufferTarget target;
    Backend::BufferHandle buffer;
  };

  struct BufferWriteCommand {
    uint16_t size;
    Backend::BufferTarget target;
  };

  struct RenderTargetSetCommand {
    Backend::RenderTargetHandle renderTarget;
  };

  struct ClearCommand {
    Backend::ClearBitMask mask;
  };

  struct ViewportSetCommand {
    uint16_t width;
    uint16_t height;
  };

  struct CullFaceSetCommand {
    Backend::CullFace face;
  };

  struct TexturePairSetCommand {
    uint8_t unit;
    Backend::TextureHandle handle;
  };

  struct TextureSetCommand {
    Backend::TextureHandle handle;
  };

  struct TextureUnitSetCommand {
    uint8_t unit;
  };

  struct BlendFunctionSetCommand {
    Backend::BlendFactor sourceFactor;
    Backend::BlendFactor destinationFactor;
  };
}

#endif
