#include "Simulation/Config.h"
#include "Simulation/Database/EntityHandle.h"
#include "Simulation/Database/Database.h"
#include "Simulation/Steering/SteeringSystem.h"
#include "Simulation/Trees.h"
#include "Simulation/Pathfinding/Map.h"
#include "Simulation/Steering/Steering.h"
#include "Simulation/ResourceType.h"
#include "Simulation/PlayMode.h"
#include "Simulation/Drag/DragSystem.h"
#include "Simulation/PhysicsHack.h"

namespace Simulation {
  namespace PlayMode {
    EntityHandle monster1;

    EntityHandle createMonster(Fixie::Num x, Fixie::Num z) {
      EntityHandle monster = Database::createEntity();

      Database::createBody(monster);
      Physics::Body body = Database::getBody(monster);
      (*body.position)[0] = x;
      (*body.position)[2] = z;
      Database::createForceDriver(monster);
      Database::createSphereCollider(monster, Fixie::Num(0.3), Physics::ColliderType::Dynamic);
      Database::createDrag(monster);

      Database::createMonster(monster);

      return monster;
    }

    void enter() {
      const uint16_t mapWidth = 16;
      const uint16_t mapHeight = 16;
      MapFieldType fields[mapWidth*mapHeight] = { MapFieldType::Grass };
      map.reset(mapWidth, mapHeight, fields);

      Trees::create(0, 0);
      Trees::create(0, 1);
      Trees::create(1, 0);

      monster1 = createMonster(2, 3);
      Database::createSteering(monster1);
      Steering steering = Database::getSteering(monster1);
      (*steering.target) = { 2, 0, 2 };

      //createMonster(3, 3);
    }

    void tick(const CommandList &commands, EventList &events) {
      Physics::Body body = Database::getBody(monster1);
      Fixie::Vector3 positionDifference = Fixie::Vector3(2, 0, 2) - (*body.position);
      if(positionDifference.calcLength() < Fixie::Num::inverse(8)) {
        if(Database::hasComponent(monster1, ComponentType::Steering)) {
          Database::destroySteering(monster1);
        }
      }

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
