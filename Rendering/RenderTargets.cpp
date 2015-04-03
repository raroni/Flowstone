#include "Misc/Error.h"
#include "SysGFX/SysGFX.h"
#include "Rendering/Textures.h"
#include "Rendering/Config.h"
#include "Rendering/RenderTargets.h"

namespace Rendering {
  namespace RenderTargets {
    HandleList handles;

    static void initializeShadowBase() {
      handles.shadowBase = SysGFX::createRenderTarget();
      SysGFX::setRenderTarget(handles.shadowBase);
      SysGFX::attachDepthTexture(Textures::list.shadowBaseBufferDepth);
      SysGFX::attachColorTexture(Textures::list.shadowVarianceDepth, 0);
    }

    static void initializeShadowBlurHorizontal() {
      handles.shadowBlurHorizontal = SysGFX::createRenderTarget();
      SysGFX::setRenderTarget(handles.shadowBlurHorizontal);
      SysGFX::attachColorTexture(Textures::list.shadowBlurVarianceDepth, 0);
    }

    static void initializeShadowBlurVertical() {
      handles.shadowBlurVertical = SysGFX::createRenderTarget();
      SysGFX::setRenderTarget(handles.shadowBlurVertical);
      SysGFX::attachColorTexture(Textures::list.shadowVarianceDepth, 0);
    }

    static void initializeGeometry() {
      handles.geometry = SysGFX::createRenderTarget();
      SysGFX::setRenderTarget(handles.geometry);
      SysGFX::attachColorTexture(Textures::list.geometryAppearance, 0);
      SysGFX::attachColorTexture(Textures::list.geometryNormal, 1);
      SysGFX::attachDepthTexture(Textures::list.geometryDepth);
      SysGFX::setDrawBufferCount(2);
    }

    static void initializeSSAOGrain() {
      handles.ssaoGrain = SysGFX::createRenderTarget();
      SysGFX::setRenderTarget(handles.ssaoGrain);
      SysGFX::attachColorTexture(Textures::list.ssaoGrainResult, 0);
    }

    static void initializeSSAOBlur() {
      handles.ssaoBlur = SysGFX::createRenderTarget();
      SysGFX::setRenderTarget(handles.ssaoBlur);
      SysGFX::attachColorTexture(Textures::list.ssaoBlur, 0);
    }

    static void initializeDownsample() {
      handles.downsample = SysGFX::createRenderTarget();
      SysGFX::setRenderTarget(handles.downsample);
      SysGFX::attachColorTexture(Textures::list.downsampleDepth, 0);
      SysGFX::attachColorTexture(Textures::list.downsampleNormal, 1);
      SysGFX::setDrawBufferCount(2);
    }

    void initialize() {
      initializeGeometry();
      initializeSSAOGrain();
      initializeSSAOBlur();
      initializeShadowBase();
      initializeShadowBlurHorizontal();
      initializeShadowBlurVertical();
      initializeDownsample();
      SysGFX::setRenderTarget(0);
    }

    void handleResolutionChange() {
      SysGFX::setRenderTarget(handles.shadowBase);
      if(!SysGFX::checkRenderTarget()) {
        fatalError("Shadow base render target not configured propertly.");
      }

      SysGFX::setRenderTarget(handles.geometry);
      if(!SysGFX::checkRenderTarget()) {
        fatalError("Geometry render target not configured propertly.");
      }

      SysGFX::setRenderTarget(handles.ssaoGrain);
      if(!SysGFX::checkRenderTarget()) {
        fatalError("SSAO grain render target not configured propertly.");
      }

      SysGFX::setRenderTarget(handles.ssaoBlur);
      if(!SysGFX::checkRenderTarget()) {
        fatalError("SSAO blur render target not configured propertly.");
      }

      SysGFX::setRenderTarget(handles.downsample);
      if(!SysGFX::checkRenderTarget()) {
        fatalError("Downsample render target not configured propertly.");
      }

      SysGFX::setRenderTarget(0);
    }
  }
}
