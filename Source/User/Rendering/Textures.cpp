#include <cstddef>
#include "Rendering/Config.h"
#include "Rendering/Backend/Functions.h"
#include "Rendering/Textures.h"

namespace Rendering {
  namespace Textures {
    List list;

    void initializeGeometryDiffuse() {
      list.geometryDiffuse = Backend::createTexture();
      Backend::setTexture(list.geometryDiffuse);
      Backend::writeTexture(800, 600, Backend::TextureFormat::RGB, NULL);
      Backend::setTextureWrap(Backend::TextureWrap::Clamp);
    }

    void initializeGeometryNormal() {
      list.geometryNormal = Backend::createTexture();
      Backend::setTexture(list.geometryNormal);
      Backend::writeTexture(800, 600, Backend::TextureFormat::SignedNormalizedRGB, NULL);
      Backend::setTextureWrap(Backend::TextureWrap::Clamp);
    }

    void initializeGeometryDepth() {
      list.geometryDepth = Backend::createTexture();
      Backend::setTexture(list.geometryDepth);
      Backend::writeTexture(800, 600, Backend::TextureFormat::Depth, NULL);
      Backend::setTextureWrap(Backend::TextureWrap::Clamp);
    }

    void initializeShadow() {
      list.shadow = Backend::createTexture();
      Backend::setTexture(list.shadow);
      Backend::writeTexture(Config::shadowMapSize, Config::shadowMapSize, Backend::TextureFormat::Depth, NULL);
      Backend::setTextureWrap(Backend::TextureWrap::Clamp);
    }

    void initialize() {
      initializeGeometryDiffuse();
      initializeGeometryNormal();
      initializeGeometryDepth();
      initializeShadow();
    }
  }
}
