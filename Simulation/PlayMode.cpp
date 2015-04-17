#include "Simulation/Database/EntityHandle.h"
#include "Simulation/Database/Database.h"
#include "Simulation/ResourceType.h"
#include "Simulation/PlayMode.h"
#include "Simulation/PhysicsHack.h"

namespace Simulation {
  namespace PlayMode {
    void enter() {
      EntityHandle tree = Database::createEntity();
      Database::createDynamicBody(tree);
      Physics::DynamicBody body = Database::getDynamicBody(tree);
      (*body.position)[0] = 2;
      Database::createResource(tree, ResourceType::Tree);
    }

    void tick(const CommandList &commands, EventList &events) {
    }

    void exit() {
    }

    ModeName getTransition() {
      return ModeName::None;
    }
  }
}
