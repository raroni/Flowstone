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

    void initializeSSAOGrainNoise() {
      list.ssaoGrainNoise = Backend::createTexture();
      Backend::setTexture(list.ssaoGrainNoise);
      Backend::setTextureWrap(Backend::TextureWrap::Repeat);
    }

    void initializeSSAOGrainResult() {
      list.ssaoGrainResult = Backend::createTexture();
      Backend::setTexture(list.ssaoGrainResult);
      Backend::setTextureWrap(Backend::TextureWrap::Clamp);
    }

    void initializeSSAOBlur() {
      list.ssaoBlur = Backend::createTexture();
      Backend::setTexture(list.ssaoBlur);
      Backend::setTextureWrap(Backend::TextureWrap::Clamp);
    }

    void initialize() {
      initializeGeometryDiffuse();
      initializeGeometryNormal();
      initializeGeometryDepth();
      initializeShadow();
      initializeSSAOGrainNoise();
      initializeSSAOGrainResult();
      initializeSSAOBlur();
      Backend::setTexture(0);
    }

    void handleResolutionChange(Resolution resolution) {
      Backend::setTexture(list.geometryDiffuse);
      Backend::writeTexture(resolution.width, resolution.height, Backend::TextureFormat::RGB, NULL);

      Backend::setTexture(list.geometryNormal);
      Backend::writeTexture(resolution.width, resolution.height, Backend::TextureFormat::SignedNormalizedRGB, NULL);

      Backend::setTexture(list.geometryDepth);
      Backend::writeTexture(resolution.width, resolution.height, Backend::TextureFormat::Depth, NULL);

      Backend::setTexture(list.ssaoGrainResult);
      Backend::writeTexture(resolution.width/Config::SSAO::downSampling, resolution.height/Config::SSAO::downSampling, Backend::TextureFormat::Red, NULL);

      Backend::setTexture(list.ssaoBlur);
      Backend::writeTexture(resolution.width/Config::SSAO::downSampling, resolution.height/Config::SSAO::downSampling, Backend::TextureFormat::Red, NULL);

      Backend::setTexture(0);
    }
  }
}
