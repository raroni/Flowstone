#include "Misc/HandleList.h"
#include "Simulation/Harvest/HarvestWorkerList.h"

namespace Simulation {
  namespace HarvestWorkerList {
    const static uint16_t max = 128;
    uint16_t indices[max];
    HarvestWorkerHandle handles[max];
    HandleList handleList(max, indices, handles);
    HarvestResourceHandle resourceHandles[max];

    HarvestWorkerHandle create(HarvestResourceHandle resourceHandle) {
      uint16_t index;
      HarvestWorkerHandle handle;
      handleList.create(&index, &handle);
      resourceHandles[index] = resourceHandle;
    }

    HarvestResourceHandle getResourceHandle(uint16_t index) {
      return resourceHandles[index];
    }

    uint16_t getCount() {
      return handleList.getCount();
    }
  }
}
