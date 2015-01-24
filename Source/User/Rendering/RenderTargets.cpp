#include "Core/Error.h"
#include "Rendering/Backend/Functions.h"
#include "Rendering/Textures.h"
#include "Rendering/Config.h"
#include "Rendering/RenderTargets.h"

namespace Rendering {
  namespace RenderTargets {
    HandleList handles;

    static void initializeShadowBase() {
      handles.shadowBase = Backend::createRenderTarget();
      Backend::setRenderTarget(handles.shadowBase);
      Backend::attachDepthTexture(Textures::list.shadowBaseBufferDepth);
      Backend::attachColorTexture(Textures::list.shadowVarianceDepth, 0);
    }

    static void initializeShadowBlurHorizontal() {
      handles.shadowBlurHorizontal = Backend::createRenderTarget();
      Backend::setRenderTarget(handles.shadowBlurHorizontal);
      Backend::attachColorTexture(Textures::list.shadowBlurVarianceDepth, 0);
    }

    static void initializeShadowBlurVertical() {
      handles.shadowBlurVertical = Backend::createRenderTarget();
      Backend::setRenderTarget(handles.shadowBlurVertical);
      Backend::attachColorTexture(Textures::list.shadowVarianceDepth, 0);
    }

    static void initializeGeometry() {
      handles.geometry = Backend::createRenderTarget();
      Backend::setRenderTarget(handles.geometry);
      Backend::attachColorTexture(Textures::list.geometryDiffuse, 0);
      Backend::attachColorTexture(Textures::list.geometryNormal, 1);
      Backend::attachDepthTexture(Textures::list.geometryDepth);
      Backend::setDrawBufferCount(2);
    }

    static void initializeSSAOGrain() {
      handles.ssaoGrain = Backend::createRenderTarget();
      Backend::setRenderTarget(handles.ssaoGrain);
      Backend::attachColorTexture(Textures::list.ssaoGrainResult, 0);
    }

    static void initializeSSAOBlur() {
      handles.ssaoBlur = Backend::createRenderTarget();
      Backend::setRenderTarget(handles.ssaoBlur);
      Backend::attachColorTexture(Textures::list.ssaoBlur, 0);
    }

    static void initializeDownsample() {
      handles.downsample = Backend::createRenderTarget();
      Backend::setRenderTarget(handles.downsample);
      Backend::attachColorTexture(Textures::list.downsampleDepth, 0);
      Backend::attachColorTexture(Textures::list.downsampleNormal, 1);
      Backend::setDrawBufferCount(2);
    }

    void initialize() {
      initializeGeometry();
      initializeSSAOGrain();
      initializeSSAOBlur();
      initializeShadowBase();
      initializeShadowBlurHorizontal();
      initializeShadowBlurVertical();
      initializeDownsample();
      Backend::setRenderTarget(0);
    }

    void handleResolutionChange() {
      Backend::setRenderTarget(handles.shadowBase);
      if(!Backend::checkRenderTarget()) {
        fatalError("Shadow base render target not configured propertly.");
      }

      Backend::setRenderTarget(handles.geometry);
      if(!Backend::checkRenderTarget()) {
        fatalError("Geometry render target not configured propertly.");
      }

      Backend::setRenderTarget(handles.ssaoGrain);
      if(!Backend::checkRenderTarget()) {
        fatalError("SSAO grain render target not configured propertly.");
      }

      Backend::setRenderTarget(handles.ssaoBlur);
      if(!Backend::checkRenderTarget()) {
        fatalError("SSAO blur render target not configured propertly.");
      }

      Backend::setRenderTarget(handles.downsample);
      if(!Backend::checkRenderTarget()) {
        fatalError("Downsample render target not configured propertly.");
      }

      Backend::setRenderTarget(0);
    }
  }
}
