#include "Rendering/Config.h"
#include "Rendering/Backend/Functions.h"
#include "Rendering/Textures.h"

namespace Rendering {
  namespace Textures {
    List list;

    void initialize() {
      list.geometryDiffuse = Backend::createTexture(800, 600, Backend::TextureFormat::RGB);
      list.geometryNormal = Backend::createTexture(800, 600, Backend::TextureFormat::SignedNormalizedRGB);
      list.geometryDepth = Backend::createTexture(800, 600, Backend::TextureFormat::Depth);
      list.shadow = Backend::createTexture(Config::shadowMapSize, Config::shadowMapSize, Backend::TextureFormat::Depth);
    }
  }
}
