#ifndef TORCH_MANAGER_H
#define TORCH_MANAGER_H

#include "Rendering/Renderer.h"
#include "Rendering/PointLightHandle.h"

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

#endif
