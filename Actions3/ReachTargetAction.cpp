#include "Simulation/Database.h"
#include "Actions3/ReachTargetAction.h"

namespace Actions3 {
  namespace ReachTargetAction {
    namespace SimDB = Simulation::Database;

    uint8_t getStateLength() {
      return 0;
    }

    uint8_t getOptionsLength() {
      return sizeof(Options);
    }

    void startExecution(Database::EntityHandle entity, void *state, const void *rawOptions) {
      const Options *options = static_cast<const Options*>(rawOptions);
      SimDB::createSteering(entity);
      SimDB::createPathfinder(entity, options->target);
    }

    void updateExecution(Database::EntityHandle, void *state, const void *options) {

    }

    bool isExecuted(Database::EntityHandle entity, void *state, const void *options) {
      return false;
    }
  }
}
