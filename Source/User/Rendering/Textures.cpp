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
      Backend::setTextureWrap(Backend::TextureWrap::Clamp);
    }

    void initializeGeometryNormal() {
      list.geometryNormal = Backend::createTexture();
      Backend::setTexture(list.geometryNormal);
      Backend::setTextureWrap(Backend::TextureWrap::Clamp);
    }

    void initializeGeometryDepth() {
      list.geometryDepth = Backend::createTexture();
      Backend::setTexture(list.geometryDepth);
      Backend::setTextureWrap(Backend::TextureWrap::Clamp);
    }

    void initializeShadow() {
      list.shadow = Backend::createTexture();
      Backend::setTexture(list.shadow);
      Backend::writeTexture(Config::shadowMapSize, Config::shadowMapSize, Backend::TextureFormat::Depth, NULL);
      Backend::setTextureWrap(Backend::TextureWrap::Clamp);
    }

    void initializeSSAONoise() {
      list.ssaoNoise = Backend::createTexture();
      Backend::setTexture(list.ssaoNoise);
      Backend::setTextureWrap(Backend::TextureWrap::Repeat);
    }

    void initializeSSAOResult() {
      list.ssaoResult = Backend::createTexture();
      Backend::setTexture(list.ssaoResult);
      Backend::setTextureWrap(Backend::TextureWrap::Clamp);
    }

    void initialize() {
      initializeGeometryDiffuse();
      initializeGeometryNormal();
      initializeGeometryDepth();
      initializeShadow();
      initializeSSAONoise();
      initializeSSAOResult();
      Backend::setTexture(0);
    }

    void handleResolutionChange(Resolution resolution) {
      Backend::setTexture(list.geometryDiffuse);
      Backend::writeTexture(resolution.width, resolution.height, Backend::TextureFormat::RGB, NULL);

      Backend::setTexture(list.geometryNormal);
      Backend::writeTexture(resolution.width, resolution.height, Backend::TextureFormat::SignedNormalizedRGB, NULL);

      Backend::setTexture(list.geometryDepth);
      Backend::writeTexture(resolution.width, resolution.height, Backend::TextureFormat::Depth, NULL);

      Backend::setTexture(list.ssaoResult);
      Backend::writeTexture(resolution.width, resolution.height, Backend::TextureFormat::Red, NULL);

      Backend::setTexture(0);
    }
  }
}
