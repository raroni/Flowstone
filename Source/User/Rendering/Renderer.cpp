#include "Rendering/ShaderLoading.h"
#include "Rendering/Input.h"
#include "Rendering/Renderer.h"

namespace Rendering {
  Renderer::Renderer() : worldRenderer(registry) { }
  void Renderer::initialize() {
    loadShaders(registry);
    glClearColor(1, 0, 0, 1);
    glEnable(GL_CULL_FACE);
    worldRenderer.initialize();
  }

  WorldRenderer& Renderer::getWorldRenderer() {
    return worldRenderer;
  }

  void Renderer::draw(const Input &input) {
    glClear(GL_COLOR_BUFFER_BIT);
    worldRenderer.draw(input.poses);
    uiRenderer.draw();
  }
}
