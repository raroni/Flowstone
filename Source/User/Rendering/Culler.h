#ifndef Rendering_CULLER_H
#define Rendering_CULLER_H

#include "Rendering/Config.h"
#include "Rendering/ObjectIndex.h"

namespace Rendering {
  class Culler {
  public:
    uint16_t cull(ObjectIndex *result) const;
    void create(ObjectIndex index);
  private:
    ObjectIndex indices[Config::maxObjects];
    uint16_t count = 0;
  };
}

#endif
