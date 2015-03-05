#include <cstddef>
#include "Rendering/Config.h"
#include "SysGFX/SysGFX.h"
#include "Rendering/Textures.h"

namespace Rendering {
  namespace Textures {
    List list;

    static void initializeGeometryAppearance() {
      list.geometryAppearance = SysGFX::createTexture();
      SysGFX::setTexture(list.geometryAppearance);
      SysGFX::setTextureWrap(SysGFX::TextureWrap::Clamp);
      SysGFX::setTextureFilter(SysGFX::TextureFilter::Nearest);
    }

    static void initializeGeometryNormal() {
      list.geometryNormal = SysGFX::createTexture();
      SysGFX::setTexture(list.geometryNormal);
      SysGFX::setTextureWrap(SysGFX::TextureWrap::Clamp);
      SysGFX::setTextureFilter(SysGFX::TextureFilter::Nearest);
    }

    static void initializeGeometryDepth() {
      list.geometryDepth = SysGFX::createTexture();
      SysGFX::setTexture(list.geometryDepth);
      SysGFX::setTextureWrap(SysGFX::TextureWrap::Clamp);
      SysGFX::setTextureFilter(SysGFX::TextureFilter::Nearest);
    }

    static void initializeShadowBaseBufferDepth() {
      list.shadowBaseBufferDepth = SysGFX::createTexture();
      SysGFX::setTexture(list.shadowBaseBufferDepth);
      SysGFX::writeTexture(Config::shadowMapSize, Config::shadowMapSize, SysGFX::TextureFormat::Depth, NULL);
    }

    static void initializeShadowVarianceDepth() {
      list.shadowVarianceDepth = SysGFX::createTexture();
      SysGFX::setTexture(list.shadowVarianceDepth);
      SysGFX::writeTexture(Config::shadowMapSize, Config::shadowMapSize, SysGFX::TextureFormat::RedGreenF32, NULL);
      SysGFX::setTextureWrap(SysGFX::TextureWrap::Clamp);
      SysGFX::setTextureFilter(SysGFX::TextureFilter::Linear);
    }

    static void initializeShadowBlurVarianceDepth() {
      list.shadowBlurVarianceDepth = SysGFX::createTexture();
      SysGFX::setTexture(list.shadowBlurVarianceDepth);
      SysGFX::writeTexture(Config::shadowMapSize, Config::shadowMapSize, SysGFX::TextureFormat::RedGreenF32, NULL);
      SysGFX::setTextureWrap(SysGFX::TextureWrap::Clamp);
      SysGFX::setTextureFilter(SysGFX::TextureFilter::Linear);
    }

    static void initializeSSAOGrainNoise() {
      list.ssaoGrainNoise = SysGFX::createTexture();
      SysGFX::setTexture(list.ssaoGrainNoise);
      SysGFX::setTextureWrap(SysGFX::TextureWrap::Repeat);
      SysGFX::setTextureFilter(SysGFX::TextureFilter::Nearest);
    }

    static void initializeSSAOGrainResult() {
      list.ssaoGrainResult = SysGFX::createTexture();
      SysGFX::setTexture(list.ssaoGrainResult);
      SysGFX::setTextureWrap(SysGFX::TextureWrap::Clamp);
      SysGFX::setTextureFilter(SysGFX::TextureFilter::Nearest);
    }

    static void initializeSSAOBlur() {
      list.ssaoBlur = SysGFX::createTexture();
      SysGFX::setTexture(list.ssaoBlur);
      SysGFX::setTextureWrap(SysGFX::TextureWrap::Clamp);
      SysGFX::setTextureFilter(SysGFX::TextureFilter::Nearest);
    }

    static void initializeDownsampleDepth() {
      list.downsampleDepth = SysGFX::createTexture();
      SysGFX::setTexture(list.downsampleDepth);
      SysGFX::setTextureWrap(SysGFX::TextureWrap::Clamp);
      SysGFX::setTextureFilter(SysGFX::TextureFilter::Nearest);
    }

    static void initializeDownsampleNormal() {
      list.downsampleNormal = SysGFX::createTexture();
      SysGFX::setTexture(list.downsampleNormal);
      SysGFX::setTextureWrap(SysGFX::TextureWrap::Clamp);
      SysGFX::setTextureFilter(SysGFX::TextureFilter::Nearest);
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
      SysGFX::setTexture(0);
    }

    void handleResolutionChange(Resolution resolution) {
      SysGFX::setTexture(list.geometryAppearance);
      SysGFX::writeTexture(resolution.width, resolution.height, SysGFX::TextureFormat::RGBA, NULL);

      SysGFX::setTexture(list.geometryNormal);
      SysGFX::writeTexture(resolution.width, resolution.height, SysGFX::TextureFormat::SignedNormalizedRGB, NULL);

      SysGFX::setTexture(list.geometryDepth);
      SysGFX::writeTexture(resolution.width, resolution.height, SysGFX::TextureFormat::Depth, NULL);

      SysGFX::setTexture(list.ssaoGrainResult);
      SysGFX::writeTexture(resolution.width/Config::SSAO::downSampling, resolution.height/Config::SSAO::downSampling, SysGFX::TextureFormat::Red, NULL);

      SysGFX::setTexture(list.ssaoBlur);
      SysGFX::writeTexture(resolution.width/Config::SSAO::downSampling, resolution.height/Config::SSAO::downSampling, SysGFX::TextureFormat::Red, NULL);

      SysGFX::setTexture(list.downsampleDepth);
      SysGFX::writeTexture(resolution.width/Config::SSAO::downSampling, resolution.height/Config::SSAO::downSampling, SysGFX::TextureFormat::RedF32, NULL);

      SysGFX::setTexture(list.downsampleNormal);
      SysGFX::writeTexture(resolution.width/Config::SSAO::downSampling, resolution.height/Config::SSAO::downSampling, SysGFX::TextureFormat::SignedNormalizedRGB, NULL);

      SysGFX::setTexture(0);
    }
  }
}
