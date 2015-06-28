#include "Simulation/Config.h"
#include "Behavior/BehaviorType.h"
#include "Behavior/System.h"
#include "Actions3/System.h"
#include "Database/EntityHandle.h"
#include "Simulation/Database.h"
#include "Simulation/Steering/SteeringSystem.h"
#include "Simulation/Trees.h"
#include "Simulation/Targeting/TargetingSystem.h"
#include "Simulation/Ticket/TicketSystem.h"
#include "Simulation/Pathfinding/Map.h"
#include "Simulation/Pathfinding/PathfindingSystem.h"
#include "Simulation/Steering/Steering.h"
#include "Simulation/ResourceType.h"
#include "Simulation/PlayMode.h"
#include "Simulation/Drag/DragSystem.h"
#include "Simulation/PhysicsHack.h"

namespace Simulation {
  namespace PlayMode {
    using namespace ::Database;

    EntityHandle createMonster(Fixie::Num x, Fixie::Num z) {
      EntityHandle monster = Database::createEntity();

      Database::createBody(monster);
      Physics::Body body = Database::getBody(monster);
      (*body.position)[0] = x;
      (*body.position)[2] = z;
      Database::createDynamicDriver(monster);
      Database::createSphereCollider(monster, Fixie::Num(0.3), Physics::ColliderType::Dynamic);
      Database::createDrag(monster);
      Database::createActions(monster);
      Database::createBehavior(monster, Behavior::BehaviorType::Monster);

      Database::createMonster(monster);

      return monster;
    }

    void enter() {
      Actions3::System::setup();
      Behavior::System::setup();

      const uint16_t mapWidth = 16;
      const uint16_t mapHeight = 16;
      MapFieldType fields[mapWidth*mapHeight] = { MapFieldType::Grass };
      map.reset(mapWidth, mapHeight, fields);

      Trees::create(0, 1);
      Trees::create(0, 0);
      Trees::create(0, 2);
      Trees::create(0, 3);
      Trees::create(0, 4);

      Trees::create(1, 0);
      Trees::create(1, 4);

      Trees::create(2, 0);
      Trees::create(2, 2);
      Trees::create(2, 4);

      Trees::create(3, 0);
      Trees::create(3, 2);
      Trees::create(3, 3);
      Trees::create(3, 4);

      Trees::create(4, 0);

      createMonster(2, 3);
    }

    void tick(const CommandList &commands, EventList &events) {
      Behavior::System::update();
      Actions3::System::update();
      TicketSystem::update();
      TargetingSystem::update();
      PathfindingSystem::update();
      SteeringSystem::update();
      DragSystem::update();
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
