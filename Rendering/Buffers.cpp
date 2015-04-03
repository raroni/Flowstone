#include <stddef.h>
#include "Rendering/BufferName.h"
#include "SysGFX/SysGFX.h"
#include "Rendering/Buffers.h"

namespace Rendering {
  namespace Buffers {
    SysGFX::BufferHandle handles[8];

    void initialize() {
      SysGFX::BufferHandle globalBuffer = SysGFX::createBuffer();
      handles[static_cast<size_t>(BufferName::Global1)] = globalBuffer;
      SysGFX::setBufferIndex(SysGFX::BufferTarget::Uniform, globalBuffer, 0);
    }
  }
}
