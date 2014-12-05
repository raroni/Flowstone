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
      if(!Backend::checkRenderTarget()) {
        fatalError("Render target not configured propertly.");
      }
      Backend::setRenderTarget(0);
    }

    static void initializeGeometry() {
      handles.geometry = Backend::createRenderTarget();
      Backend::setRenderTarget(handles.geometry);
      Backend::RenderBufferHandle depthBuffer = Backend::createRenderBuffer(800, 600);
      Backend::setRenderBuffer(depthBuffer);
      Backend::attachRenderBuffer(depthBuffer);
      Backend::attachColorTexture(Textures::list.geometryDiffuse, 0);
      Backend::attachColorTexture(Textures::list.geometryLambert, 1);
      Backend::setDrawBufferCount(2);
      if(!Backend::checkRenderTarget()) {
        fatalError("Render target not configured propertly.");
      }
      Backend::setRenderTarget(0);
    }

    void initialize() {
      initializeGeometry();
      initializeShadow();
    }
  }
}
