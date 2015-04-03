#ifndef CLIENT_TORCH_MANAGER_H
#define CLIENT_TORCH_MANAGER_H

#include "Rendering/Renderer.h"
#include "Rendering/PointLightHandle.h"

namespace Client {
  class TorchManager {
  public:
    typedef Rendering::Renderer Renderer;
    TorchManager(Renderer &renderer) : renderer(renderer) { }
    void initialize();
    void create(float x, float z);
  private:
    Renderer &renderer;
    Rendering::StaticMeshIndex meshIndex;
  };
}

#endif
