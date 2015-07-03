#include <assert.h>
#include "Simulation/Config.h"
#include "Simulation/Harvest/HarvestResourceList.h"
#include "Simulation/Harvest/HarvestSystem.h"

namespace Simulation {
  namespace HarvestSystem {
    HarvestWorkerHandle createWorker(HarvestResourceHandle handle) {

    }

    HarvestResourceHandle createResource(HarvestResourceType type) {
      return HarvestResourceList::create(type);
    }

    void destroyResource(HarvestResourceHandle resource) {
      HarvestResourceList::destroy(resource);
    }
  }
}
