#ifndef RENDERING_CULL_RESULT_H
#define RENDERING_CULL_RESULT_H

#include "Rendering/BoneMeshDrawHandle.h"
#include "Rendering/StaticMeshDrawHandle.h"
#include "Rendering/CullResultRange.h"
#include "Rendering/CullGroupIndex.h"
#include "Rendering/Config.h"

namespace Rendering {
  struct CullResult {
    static const uint16_t max = 256;
    uint16_t indices[max];
    uint16_t count;
    CullResultRange ranges[Config::cullGroupsCount];
    void clear();
    void addIndex(uint16_t index);
    const CullResultRange& getRange(CullGroupIndex group) const;
    void storeRange(CullGroupIndex group, uint16_t start, uint16_t end);
  };
};

#endif
