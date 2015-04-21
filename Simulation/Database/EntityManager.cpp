#include "Simulation/Database/EntityManager.h"

namespace Simulation {
  namespace EntityManager {
    uint16_t count = 0;
    EntityHandle handles[Config::entityMax];

    EntityHandle create() {
      EntityHandle handle = count; // quick'n dirty, should use some kind of pool
      handles[count] = handle;
      count++;
      return handle;
    }

    uint16_t getCount() {
      return count;
    }
  }
}
