#include "Rendering/Backend/Functions.h"
#include "Rendering/Textures.h"

namespace Rendering {
  namespace Textures {
    List list;

    void initialize() {
      list.geometryDiffuse = Backend::createTexture(800, 600, Backend::TextureFormat::RGB);
      list.geometryLambert = Backend::createTexture(800, 600, Backend::TextureFormat::RED);
    }
  }
}