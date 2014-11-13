#include "Rendering2/OpenGL/Setup.h"

struct Pose;

namespace Rendering2 {
  class Renderer {
    Backend backend;
  public:
    void initialize() {
      backend.initialize();
    }
    AnimatedMeshIndex createAnimatedMesh(const AnimatedVertex *vertices, const size_t vertexCount, const uint16_t *indices, const size_t indexCount) {
      return backend.createAnimatedMesh(vertices, vertexCount, indices, indexCount);
    }
    void draw() {
      backend.clear();
    }
  };
}
