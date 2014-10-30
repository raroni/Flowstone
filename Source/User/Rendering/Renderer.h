#ifndef RENDERING_RENDERER_H
#define RENDERING_RENDERER_H

#include "Rendering/ShaderRegistry.h"
#include "Rendering/WorldRenderer.h"
#include "Rendering/UIRenderer.h"

namespace Quanta {
  class Matrix4;
}

namespace Rendering {
  class Renderer {
    ShaderRegistry registry;
    WorldRenderer worldRenderer;
    UIRenderer uiRenderer;
  public:
    Renderer();
    void initialize();
    WorldRenderer& getWorldRenderer();
    void draw(const Quanta::Matrix4 *worldPoses);
  };
}

#endif
