#include <assert.h>
#include "Simulation/Config.h"
#include "Simulation/Harvest/HarvestSystem.h"

namespace Simulation {
  namespace HarvestSystem {
    uint16_t count = 0;
    HarvestResourceType types[Config::resourceMax];

    HarvestResourceHandle createResource(HarvestResourceType type) {
      assert(count != Config::resourceMax);
      types[count] = type;

      // todo: should use free list
      return count++;
    }
  }
}
