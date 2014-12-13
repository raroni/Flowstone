#ifndef RENDERING_CULL_RESULT_H
#define RENDERING_CULL_RESULT_H

#include "Rendering/BoneMeshInstanceIndex.h"
#include "Rendering/StaticMeshInstanceIndex.h"
#include "Rendering/Config.h"

namespace Rendering {
  class CullResult {
  public:
    void addBoneInstance(BoneMeshInstanceIndex boneInstance);
    void addStaticInstance(StaticMeshInstanceIndex staticInstance);
    void clear();
    struct {
      BoneMeshInstanceIndex list[Config::maxCulledBoneInstances];
      uint16_t count;
    } boneInstances;
    struct {
      StaticMeshInstanceIndex list[Config::maxCulledStaticInstances];
      uint16_t count;
    } staticInstances;
  };
}

#endif
