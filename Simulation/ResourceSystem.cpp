#include <assert.h>
#include "Simulation/Config.h"
#include "Simulation/ResourceSystem.h"

namespace Simulation {
  namespace ResourceSystem {
    uint16_t count = 0;
    ResourceType types[Config::resourceMax];

    ResourceHandle create(ResourceType type) {
      assert(count != Config::resourceMax);
      types[count] = type;

      // todo: should use free list
      return count++;
    }
  }
}
