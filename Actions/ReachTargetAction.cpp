#include "Simulation/Database.h"
#include "Actions/ReachTargetAction.h"

namespace Actions {
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

    void updateExecution(Database::EntityHandle entity, void *state, const void *rawOptions) {
      const Options *options = static_cast<const Options*>(rawOptions);
      Physics::Body body = SimDB::getBody(entity);
      Fixie::Vector3 *position = body.position;
      Fixie::Vector2 position2D(
        (*position)[0],
        (*position)[2]
      );
      Fixie::Vector2 difference = position2D - options->target;
      if(difference.calcLength() <= options->tolerance) {
        SimDB::destroySteering(entity);
        SimDB::destroyPathfinder(entity);
      }
    }

    bool isExecuted(Database::EntityHandle entity, void *state, const void *options) {
      return !SimDB::hasComponent(entity, Simulation::ComponentType::Pathfinder);
    }
  }
}
