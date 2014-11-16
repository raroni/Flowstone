#ifndef RENDERING2_CULLER_H
#define RENDERING2_CULLER_H

#include "Rendering2/Config.h"
#include "Rendering2/ObjectIndex.h"

namespace Rendering2 {
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
