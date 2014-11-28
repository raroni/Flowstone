#include <stddef.h>
#include "Rendering/BufferName.h"
#include "Rendering/Backend/Functions.h"
#include "Rendering/Buffers.h"

namespace Rendering {
  namespace Buffers {
    Backend::BufferHandle handles[8];

    void initialize() {
      Backend::BufferHandle globalBuffer = Backend::createBuffer();
      handles[static_cast<size_t>(BufferName::Global1)] = globalBuffer;
      Backend::setBufferIndex(Backend::BufferTarget::Uniform, 0, globalBuffer);
    }
  }
}
