#include "Core/Error.h"
#include "Rendering/Backend/Functions.h"
#include "Rendering/Textures.h"
#include "Rendering/RenderTargets.h"

namespace Rendering {
  namespace RenderTargets {
    HandleList handles;

    void initialize() {
      handles.geometry = Backend::createRenderTarget();
      Backend::setRenderTarget(handles.geometry);
      Backend::RenderBufferHandle depthBuffer = Backend::createRenderBuffer(800, 600);
      Backend::setRenderBuffer(depthBuffer);
      Backend::attachRenderBuffer(depthBuffer);
      Backend::attachTexture(Textures::list.geometryDiffuse, 0);
      Backend::attachTexture(Textures::list.geometryLambert, 1);
      Backend::setDrawBufferCount(2);
      if(!Backend::checkRenderTarget()) {
        fatalError("Render target not configured propertly.");
      }
      Backend::setRenderTarget(0);
    }
  }
}
