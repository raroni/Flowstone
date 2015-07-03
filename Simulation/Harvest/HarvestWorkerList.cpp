#include "Misc/HandleList.h"
#include "Simulation/Harvest/HarvestWorkerList.h"

namespace Simulation {
  namespace HarvestWorkerList {
    const static uint16_t max = 128;
    uint16_t indices[max];
    HarvestWorkerHandle handles[max];
    HandleList handleList(max, indices, handles);
    Database::EntityHandle workerEntityHandles[max];
    Database::EntityHandle resourceEntityHandles[max];
    HarvestResourceHandle resourceHandles[max];

    HarvestWorkerHandle create(Database::EntityHandle worker, Database::EntityHandle resource, HarvestResourceHandle resourceHandle) {
      uint16_t index;
      HarvestWorkerHandle handle;
      handleList.create(&index, &handle);
      resourceHandles[index] = resourceHandle;
      workerEntityHandles[index] = worker;
      resourceEntityHandles[index] = resource;
      return handle;
    }

    HarvestResourceHandle getResourceHandle(uint16_t index) {
      return resourceHandles[index];
    }

    uint16_t getCount() {
      return handleList.getCount();
    }
  }
}
