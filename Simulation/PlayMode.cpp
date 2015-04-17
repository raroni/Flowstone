#include "Simulation/Database/EntityHandle.h"
#include "Simulation/Database/Database.h"
#include "Simulation/PlayMode.h"
#include "Simulation/PhysicsHack.h"

namespace Simulation {
  namespace PlayMode {
    void enter() {
      EntityHandle tree = Database::createEntity();
      Physics::DynamicBodyIndex i = Database::createDynamicBody(tree);

      Physics::DynamicBody body2 = Database::getDynamicBody(tree);
      Physics::DynamicBody body3 = physicsEngine.getDynamicBody(i);


      EntityHandle treeb = Database::createEntity();
      Physics::DynamicBodyIndex ib = Database::createDynamicBody(treeb);

      Physics::DynamicBody body2b = Database::getDynamicBody(tree);
      Physics::DynamicBody body3b = physicsEngine.getDynamicBody(ib);
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
