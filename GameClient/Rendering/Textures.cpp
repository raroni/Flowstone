#include <cstddef>
#include "Rendering/Config.h"
#include "Rendering/Backend/Functions.h"
#include "Rendering/Textures.h"

namespace Rendering {
  namespace Textures {
    List list;

    static void initializeGeometryAppearance() {
      list.geometryAppearance = Backend::createTexture();
      Backend::setTexture(list.geometryAppearance);
      Backend::setTextureWrap(Backend::TextureWrap::Clamp);
      Backend::setTextureFilter(Backend::TextureFilter::Nearest);
    }

    static void initializeGeometryNormal() {
      list.geometryNormal = Backend::createTexture();
      Backend::setTexture(list.geometryNormal);
      Backend::setTextureWrap(Backend::TextureWrap::Clamp);
      Backend::setTextureFilter(Backend::TextureFilter::Nearest);
    }

    static void initializeGeometryDepth() {
      list.geometryDepth = Backend::createTexture();
      Backend::setTexture(list.geometryDepth);
      Backend::setTextureWrap(Backend::TextureWrap::Clamp);
      Backend::setTextureFilter(Backend::TextureFilter::Nearest);
    }

    static void initializeShadowBaseBufferDepth() {
      list.shadowBaseBufferDepth = Backend::createTexture();
      Backend::setTexture(list.shadowBaseBufferDepth);
      Backend::writeTexture(Config::shadowMapSize, Config::shadowMapSize, Backend::TextureFormat::Depth, NULL);
    }

    static void initializeShadowVarianceDepth() {
      list.shadowVarianceDepth = Backend::createTexture();
      Backend::setTexture(list.shadowVarianceDepth);
      Backend::writeTexture(Config::shadowMapSize, Config::shadowMapSize, Backend::TextureFormat::RedGreenF32, NULL);
      Backend::setTextureWrap(Backend::TextureWrap::Clamp);
      Backend::setTextureFilter(Backend::TextureFilter::Linear);
    }

    static void initializeShadowBlurVarianceDepth() {
      list.shadowBlurVarianceDepth = Backend::createTexture();
      Backend::setTexture(list.shadowBlurVarianceDepth);
      Backend::writeTexture(Config::shadowMapSize, Config::shadowMapSize, Backend::TextureFormat::RedGreenF32, NULL);
      Backend::setTextureWrap(Backend::TextureWrap::Clamp);
      Backend::setTextureFilter(Backend::TextureFilter::Linear);
    }

    static void initializeSSAOGrainNoise() {
      list.ssaoGrainNoise = Backend::createTexture();
      Backend::setTexture(list.ssaoGrainNoise);
      Backend::setTextureWrap(Backend::TextureWrap::Repeat);
      Backend::setTextureFilter(Backend::TextureFilter::Nearest);
    }

    static void initializeSSAOGrainResult() {
      list.ssaoGrainResult = Backend::createTexture();
      Backend::setTexture(list.ssaoGrainResult);
      Backend::setTextureWrap(Backend::TextureWrap::Clamp);
      Backend::setTextureFilter(Backend::TextureFilter::Nearest);
    }

    static void initializeSSAOBlur() {
      list.ssaoBlur = Backend::createTexture();
      Backend::setTexture(list.ssaoBlur);
      Backend::setTextureWrap(Backend::TextureWrap::Clamp);
      Backend::setTextureFilter(Backend::TextureFilter::Nearest);
    }

    static void initializeDownsampleDepth() {
      list.downsampleDepth = Backend::createTexture();
      Backend::setTexture(list.downsampleDepth);
      Backend::setTextureWrap(Backend::TextureWrap::Clamp);
      Backend::setTextureFilter(Backend::TextureFilter::Nearest);
    }

    static void initializeDownsampleNormal() {
      list.downsampleNormal = Backend::createTexture();
      Backend::setTexture(list.downsampleNormal);
      Backend::setTextureWrap(Backend::TextureWrap::Clamp);
      Backend::setTextureFilter(Backend::TextureFilter::Nearest);
    }

    void initialize() {
      initializeGeometryAppearance();
      initializeGeometryNormal();
      initializeGeometryDepth();
      initializeShadowBaseBufferDepth();
      initializeShadowVarianceDepth();
      initializeShadowBlurVarianceDepth();
      initializeSSAOGrainNoise();
      initializeSSAOGrainResult();
      initializeSSAOBlur();
      initializeDownsampleDepth();
      initializeDownsampleNormal();
      Backend::setTexture(0);
    }

    void handleResolutionChange(Resolution resolution) {
      Backend::setTexture(list.geometryAppearance);
      Backend::writeTexture(resolution.width, resolution.height, Backend::TextureFormat::RGBA, NULL);

      Backend::setTexture(list.geometryNormal);
      Backend::writeTexture(resolution.width, resolution.height, Backend::TextureFormat::SignedNormalizedRGB, NULL);

      Backend::setTexture(list.geometryDepth);
      Backend::writeTexture(resolution.width, resolution.height, Backend::TextureFormat::Depth, NULL);

      Backend::setTexture(list.ssaoGrainResult);
      Backend::writeTexture(resolution.width/Config::SSAO::downSampling, resolution.height/Config::SSAO::downSampling, Backend::TextureFormat::Red, NULL);

      Backend::setTexture(list.ssaoBlur);
      Backend::writeTexture(resolution.width/Config::SSAO::downSampling, resolution.height/Config::SSAO::downSampling, Backend::TextureFormat::Red, NULL);

      Backend::setTexture(list.downsampleDepth);
      Backend::writeTexture(resolution.width/Config::SSAO::downSampling, resolution.height/Config::SSAO::downSampling, Backend::TextureFormat::RedF32, NULL);

      Backend::setTexture(list.downsampleNormal);
      Backend::writeTexture(resolution.width/Config::SSAO::downSampling, resolution.height/Config::SSAO::downSampling, Backend::TextureFormat::SignedNormalizedRGB, NULL);

      Backend::setTexture(0);
    }
  }
}
