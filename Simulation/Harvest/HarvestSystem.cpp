#include <assert.h>
#include "Simulation/Config.h"
#include "Simulation/Harvest/HarvestResourceList.h"
#include "Simulation/Harvest/HarvestWorkerList.h"
#include "Simulation/Harvest/HarvestSystem.h"

namespace Simulation {
  namespace HarvestSystem {
    HarvestWorkerHandle createWorker(HarvestResourceHandle handle) {
      return HarvestWorkerList::create(handle);
    }

    HarvestResourceHandle createResource(HarvestResourceType type) {
      return HarvestResourceList::create(type);
    }

    void destroyResource(HarvestResourceHandle resource) {
      HarvestResourceList::destroy(resource);
    }

    void update() {
      uint16_t count = HarvestWorkerList::getCount();
      for(uint16_t i=0; i<count; ++i) {

      }
    }
  }
}
