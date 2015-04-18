#include "Simulation/Database/EntityHandle.h"
#include "Simulation/Database/Database.h"
#include "Simulation/ResourceType.h"
#include "Simulation/PlayMode.h"
#include "Simulation/PhysicsHack.h"

namespace Simulation {
  namespace PlayMode {
    EntityHandle monster;

    void createTree() {
      EntityHandle tree = Database::createEntity();

      Database::createStaticBody(tree);
      Physics::StaticBody body = Database::getStaticBody(tree);
      (*body.position)[0] = -2;

      Database::createResource(tree, ResourceType::Tree);
    }

    void createMonster() {
      monster = Database::createEntity();

      Database::createDynamicBody(monster);
      Physics::DynamicBody body = Database::getDynamicBody(monster);
      (*body.position)[0] = 2;
      (*body.position)[2] = -0.25;

      Database::createMonster(monster);
    }

    void enter() {
      createTree();
      createMonster();
    }

    void tick(const CommandList &commands, EventList &events) {
      Physics::DynamicBody body = Database::getDynamicBody(monster);
      (*body.position)[0] += Fixie::Num(-0.01);
    }

    void exit() {
    }

    ModeName getTransition() {
      return ModeName::None;
    }
  }
}
