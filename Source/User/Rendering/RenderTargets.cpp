#include "Core/Error.h"
#include "Rendering/Backend/Functions.h"
#include "Rendering/RenderTargets.h"

namespace Rendering {
  namespace RenderTargets {
    void initialize() {
      handles.geometry = Backend::createRenderTarget();
      Backend::TextureHandle diffuseTexture = Backend::createTexture(800, 600, Backend::TextureFormat::RGB);
      Backend::TextureHandle lambertTexture = Backend::createTexture(800, 600, Backend::TextureFormat::RED);

      Backend::setRenderTarget(handles.geometry);
      Backend::attachTexture(diffuseTexture, 0);
      Backend::attachTexture(lambertTexture, 1);

      if(!Backend::checkRenderTarget()) {
        fatalError("Render target not configured propertly.");
      }

      Backend::setRenderTarget(0);
    }
  }
}
