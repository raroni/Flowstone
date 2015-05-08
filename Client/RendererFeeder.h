#ifndef CLIENT_RENDERER_FEEDER_H
#define CLIENT_RENDERER_FEEDER_H

#include "Interpolation/Index.h"
#include "Animation/PoseIndex.h"
#include "Rendering/StaticMeshInstanceHandle.h"
#include "Rendering/BoneMeshInstanceHandle.h"

namespace Client {
  class RendererFeeder {
  public:
    uint16_t setupBoneMesh(Interpolation::Index interpolation, Animation::PoseIndex pose, Rendering::BoneMeshInstanceHandle mesh);
    void update();
  private:
    struct BoneBinding {
      uint8_t interpolation;
      Animation::PoseIndex pose;
      Rendering::BoneMeshInstanceHandle mesh;
    };
    struct {
      BoneBinding list[128];
      uint8_t count = 0;
    } boneBindings;
  };

  extern RendererFeeder rendererFeeder;
}

#endif
