#ifndef RENDERER_FEEDER_H
#define RENDERER_FEEDER_H

#include "Core/Physics/StaticBodyIndex.h"
#include "Core/Physics/DynamicBodyIndex.h"
#include "Rendering/StaticMeshInstanceIndex.h"
#include "Rendering/BoneMeshInstanceIndex.h"

namespace Physics {
  class Engine;
}

namespace Rendering {
  class Renderer;
}

class FrameInterpolator;

class RendererFeeder {
public:
  RendererFeeder(const Physics::Engine &physicsEngine, Rendering::Renderer &renderer, const FrameInterpolator &interpolator);
  void bindStaticStatic(Physics::StaticBodyIndex body, Rendering::StaticMeshInstanceIndex mesh);
  void bindDynamicBone(uint8_t interpolation, Rendering::BoneMeshInstanceIndex mesh);
  void update();
private:
  struct DynamicBoneBinding {
    uint8_t interpolation;
    Rendering::BoneMeshInstanceIndex mesh;
  };
  struct {
    DynamicBoneBinding list[128];
    uint8_t count = 0;
  } dynamicBoneBindings;
  struct StaticStaticBinding {
    Physics::StaticBodyIndex body;
    Rendering::StaticMeshInstanceIndex mesh;
  };
  struct {
    StaticStaticBinding list[128];
    uint8_t count = 0;
  } staticStaticBindings;
  const Physics::Engine &physicsEngine;
  const FrameInterpolator &interpolator;
  Rendering::Renderer &renderer;
};

#endif
