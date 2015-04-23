#include "Simulation/Config.h"
#include "Simulation/Database/EntityHandle.h"
#include "Simulation/Database/Database.h"
#include "Simulation/ResourceType.h"
#include "Simulation/PlayMode.h"
#include "Simulation/PhysicsHack.h"

namespace Simulation {
  namespace PlayMode {
    EntityHandle monster1;

    void createTree() {
      EntityHandle tree = Database::createEntity();

      Database::createBody(tree);
      Physics::Body body = Database::getBody(tree);
      (*body.position)[0] = -2;

      Database::createSphereCollider(tree, Fixie::Num(0.25), Physics::ColliderType::Static);

      Database::createResource(tree, ResourceType::Tree);
    }

    EntityHandle createMonster(Fixie::Num x, Fixie::Num z) {
      EntityHandle monster = Database::createEntity();

      Database::createBody(monster);
      Physics::Body body = Database::getBody(monster);
      (*body.position)[0] = x;
      (*body.position)[2] = z;
      Database::createForceDriver(monster);
      Database::createSphereCollider(monster, Fixie::Num(0.3), Physics::ColliderType::Dynamic);

      Database::createMonster(monster);

      return monster;
    }

    void enter() {
      createTree();
      monster1 = createMonster(0.5, -0.1);
      createMonster(-0.8, 0);
    }

    void tick(const CommandList &commands, EventList &events) {
      Physics::ForceDriver driver = Database::getForceDriver(monster1);
      (*driver.force)[0] *= Fixie::Num(0.5);
      (*driver.force)[0] += Fixie::Num(-0.02);

      static_assert(Physics::Config::stepDuration == Config::tickDuration, "Physics and simulation must agree on tick duration.");
      physicsEngine.simulate();
    }

    void exit() {
    }

    ModeName getTransition() {
      return ModeName::None;
    }
  }
}
