#ifndef RENDERER_FEEDER_H
#define RENDERER_FEEDER_H

#include "Common/Physics/StaticBodyIndex.h"
#include "Common/Physics/DynamicBodyIndex.h"
#include "Interpolation/Index.h"
#include "Rendering/StaticMeshInstanceHandle.h"
#include "Rendering/BoneMeshInstanceHandle.h"

namespace Physics {
  class Engine;
}

namespace Rendering {
  class Renderer;
}

namespace Animation {
  class Animator;
}

namespace Interpolation {
  class Interpolater;
}

class RendererFeeder {
public:
  RendererFeeder(
    const Physics::Engine &physicsEngine,
    const Interpolation::Interpolater &interpolator,
    const Animation::Animator &animator,
    Rendering::Renderer &renderer
  );
  void bindStaticStatic(Physics::StaticBodyIndex body, Rendering::StaticMeshInstanceHandle mesh);
  void setupBoneMesh(Interpolation::Index interpolation, Animation::PoseIndex pose, Rendering::BoneMeshInstanceHandle mesh);
  void update();
private:
  struct DynamicBoneBinding {
    uint8_t interpolation;
    Animation::PoseIndex pose;
    Rendering::BoneMeshInstanceHandle mesh;
  };
  struct {
    DynamicBoneBinding list[128];
    uint8_t count = 0;
  } dynamicBoneBindings;
  struct StaticStaticBinding {
    Physics::StaticBodyIndex body;
    Rendering::StaticMeshInstanceHandle mesh;
  };
  struct {
    StaticStaticBinding list[128];
    uint8_t count = 0;
  } staticStaticBindings;
  const Physics::Engine &physicsEngine;
  const Interpolation::Interpolater &interpolator;
  const Animation::Animator &animator;
  Rendering::Renderer &renderer;
};

#endif
