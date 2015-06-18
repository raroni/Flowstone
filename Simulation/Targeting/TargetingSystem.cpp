#include "Simulation/Targeting/TargetingList.h"
#include "Simulation/Targeting/TargetingSystem.h"

namespace Simulation {
  namespace TargetingSystem {
    TargetingHandle create(Database::EntityHandle targetEntity) {
      return TargetingList::create(targetEntity);
    }
  }
}
