#ifndef RENDERING_CULL_RESULT_H
#define RENDERING_CULL_RESULT_H

#include "Rendering/BoneMeshInstanceIndex.h"
#include "Rendering/StaticMeshInstanceIndex.h"
#include "Rendering/CullResultRange.h"
#include "Rendering/CullGroupIndex.h"
#include "Rendering/Config.h"

namespace Rendering {
  struct CullResult {
    uint16_t indices[256];
    uint16_t count;
    CullResultRange ranges[Config::cullGroupsCount];
    void clear();
    void addIndex(uint16_t index);
    const CullResultRange& getRange(CullGroupIndex group);
    void storeRange(CullGroupIndex group, uint16_t start, uint16_t end);
  };
};

#endif
