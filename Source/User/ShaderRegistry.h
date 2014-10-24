#include <stdint.h>
#include "Conrad/Array.h"

typedef size_t ShaderHandle;

enum class ShaderName {
  Test
};

class ShaderRegistry {
  static const uint8_t maxHandlesCount = 20;
  Array<GLuint, maxHandlesCount> handles;
  size_t handlesCount = 0;
  Array<size_t, maxHandlesCount> offsets;
public:
  void addHandle(ShaderName name, GLuint handle) {
    handles[handlesCount] = handle;
    offsets[static_cast<size_t>(name)] = handlesCount;
    handlesCount++;
  }
  GLuint getHandle(ShaderName name) const {
    size_t offset = offsets[static_cast<size_t>(name)];
    return handles[offset];
  }
};
