#include "Misc/HandleList.h"
#include "Simulation/Targeting/TargetingList.h"

namespace Simulation {
  namespace TargetingList {
    static const uint16_t max = 32;
    uint16_t indices[max];
    uint16_t handles[max];
    HandleList handleList(max, indices, handles);
    Database::EntityHandle entities[max];
    Fixie::Vector3 positions[max];

    TargetingHandle create(Database::EntityHandle entity) {
      uint16_t index;
      TargetingHandle handle;
      handleList.create(&index, &handle);
      entities[index] = entity;
      return handle;
    }

    uint16_t getIndex(TargetingHandle handle) {
      return handleList.getIndex(handle);
    }

    Database::EntityHandle getEntity(uint16_t index) {
      return entities[index];
    }

    void updatePosition(uint16_t index, const Fixie::Vector3 *position) {
      positions[index] = *position;
    }
  }
}
