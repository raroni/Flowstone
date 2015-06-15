#include "Simulation/Config.h"
#include "Behavior/BehaviorType.h"
#include "Behavior/System.h"
#include "Actions/System.h"
#include "Database/EntityHandle.h"
#include "Simulation/Database.h"
#include "Simulation/Steering/SteeringSystem.h"
#include "Simulation/Trees.h"
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
    EntityHandle monster1;

    struct {
      uint16_t x = 4;
      uint16_t z = 4;
    } dummyTarget;

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
      Actions::System::setup();
      Behavior::System::setup();

      const uint16_t mapWidth = 16;
      const uint16_t mapHeight = 16;
      MapFieldType fields[mapWidth*mapHeight] = { MapFieldType::Grass };
      map.reset(mapWidth, mapHeight, fields);

      Trees::create(0, 0);
      Trees::create(0, 1);
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

      monster1 = createMonster(2, 3);
      Database::createSteering(monster1);
      Database::createPathfinder(monster1, { dummyTarget.x, dummyTarget.z });

      //createMonster(3, 3);
    }

    void tick(const CommandList &commands, EventList &events) {
      Physics::Body body = Database::getBody(monster1);
      Fixie::Vector3 positionDifference = Fixie::Vector3(dummyTarget.x, 0, dummyTarget.z) - (*body.position);
      if(positionDifference.calcLength() < Fixie::Num::inverse(8)) {
        if(Database::hasComponent(monster1, ComponentType::Steering)) {
          Database::destroySteering(monster1);
          Database::destroyPathfinder(monster1);
        }
      }
      Behavior::System::update();
      Actions::System::update();
      TicketSystem::update();
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
