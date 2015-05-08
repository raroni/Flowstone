#ifndef CLIENT_TORCH_MANAGER_H
#define CLIENT_TORCH_MANAGER_H

#include "Rendering/PointLightHandle.h"

namespace Client {
  class TorchManager {
  public:
    void initialize();
    void create(float x, float z);
  private:
    Rendering::StaticMeshIndex meshIndex;
  };
}

#endif
