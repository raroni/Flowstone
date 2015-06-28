#include <assert.h>
#include "Simulation/Database.h"
#include "Simulation/Targeting/TargetingList.h"
#include "Simulation/Targeting/TargetingSystem.h"

namespace Simulation {
  namespace TargetingSystem {
    const uint8_t max = 32;
    struct {
      TargetingHandle values[max];
      uint8_t count = 0;
    } newHandles;

    TargetingHandle create(::Database::EntityHandle targetEntity) {
      assert(max != newHandles.count);
      TargetingHandle handle = TargetingList::create(targetEntity);
      newHandles.values[newHandles.count++] = handle;
      return handle;
    }

    void update() {
      for(uint8_t i=0; i<newHandles.count; ++i) {
        uint16_t index = TargetingList::getIndex(newHandles.values[i]);
        ::Database::EntityHandle targetEntity = TargetingList::getEntity(i);
        Physics::Body targetBody = Database::getBody(targetEntity);
        TargetingList::updatePosition(index, targetBody.position);
      }
      newHandles.count = 0;
    }
  }
}
