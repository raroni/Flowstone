#include "Misc/HandleList.h"
#include "Simulation/Harvest/HarvestResourceList.h"

namespace Simulation {
  namespace HarvestResourceList {
    const static uint16_t max = 128;
    uint16_t indices[max];
    HarvestResourceHandle handles[max];
    HandleList handleList(max, indices, handles);
    HarvestResourceType types[max];

    HarvestResourceHandle create(HarvestResourceType type) {
      uint16_t index;
      HarvestResourceHandle handle;
      handleList.create(&index, &handle);
      types[index] = type;
      return handle;
    }

    void destroy(HarvestResourceHandle handle) {
      uint16_t sourceIndex, destinationIndex;
      handleList.destroy(handle, &sourceIndex, &destinationIndex);
      types[destinationIndex] = types[sourceIndex];
    }
  }
}
