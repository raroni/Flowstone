#include "Core/Error.h"
#include "Rendering/Backend/Functions.h"
#include "Rendering/Textures.h"
#include "Rendering/RenderTargets.h"

namespace Rendering {
  namespace RenderTargets {
    HandleList handles;

    static void initializeShadow() {
      handles.shadow = Backend::createRenderTarget();
      Backend::setRenderTarget(handles.shadow);
      Backend::attachDepthTexture(Textures::list.shadow);
      Backend::disableDrawBuffer();
    }

    static void initializeGeometry() {
      handles.geometry = Backend::createRenderTarget();
      Backend::setRenderTarget(handles.geometry);
      Backend::attachColorTexture(Textures::list.geometryDiffuse, 0);
      Backend::attachColorTexture(Textures::list.geometryNormal, 1);
      Backend::attachDepthTexture(Textures::list.geometryDepth);
      Backend::setDrawBufferCount(2);
    }

    static void initializeSSAO() {
      handles.ssao = Backend::createRenderTarget();
      Backend::setRenderTarget(handles.ssao);
      Backend::attachColorTexture(Textures::list.ssaoResult, 0);
    }

    void initialize() {
      initializeGeometry();
      initializeSSAO();
      initializeShadow();
      Backend::setRenderTarget(0);
    }

    void handleResolutionChange() {
      Backend::setRenderTarget(handles.shadow);
      if(!Backend::checkRenderTarget()) {
        fatalError("Shadow render target not configured propertly.");
      }

      Backend::setRenderTarget(handles.geometry);
      if(!Backend::checkRenderTarget()) {
        fatalError("Geometry render target not configured propertly.");
      }

      Backend::setRenderTarget(handles.ssao);
      if(!Backend::checkRenderTarget()) {
        fatalError("SSAO render target not configured propertly.");
      }

      Backend::setRenderTarget(0);
    }
  }
}
