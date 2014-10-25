#include "Rendering/ShaderLoading.h"
#include "Rendering/Renderer.h"

namespace Rendering {
  Renderer::Renderer() : worldRenderer(registry) { }
  void Renderer::initialize() {
    loadShaders(registry);
    glClearColor(1, 0, 0, 1);
  }

  WorldRenderer& Renderer::getWorldRenderer() {
    return worldRenderer;
  }

  void Renderer::draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    worldRenderer.draw();
    uiRenderer.draw();
  }
}
