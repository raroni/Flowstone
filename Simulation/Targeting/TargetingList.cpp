#include "Misc/HandleList.h"
#include "Simulation/Targeting/TargetingList.h"

namespace Simulation {
  namespace TargetingList {
    static const uint16_t max = 32;
    uint16_t indices[max];
    uint16_t handles[max];
    HandleList handleList(max, indices, handles);
    Database::EntityHandle targetEntities[max];

    TargetingHandle create(Database::EntityHandle targetEntity) {
      uint16_t index;
      TargetingHandle handle;
      handleList.create(&index, &handle);
      targetEntities[index] = targetEntity;
      return handle;
    }
  }
}
