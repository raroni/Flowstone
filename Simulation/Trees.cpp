#include "Simulation/Database/EntityHandle.h"
#include "Simulation/Database/Database.h"
#include "Simulation/Pathfinding/Map.h"
#include "Simulation/Pathfinding/MapFieldIndex.h"
#include "Simulation/Pathfinding/MapFieldType.h"
#include "Simulation/Trees.h"

namespace Simulation {
  namespace Trees {
    void create(uint16_t x, uint16_t z) {
      EntityHandle tree = Database::createEntity();

      Database::createBody(tree);
      Physics::Body body = Database::getBody(tree);
      (*body.position)[0] = x;
      (*body.position)[2] = z;

      Database::createSphereCollider(tree, Fixie::Num(0.25), Physics::ColliderType::Static);

      Database::createResource(tree, ResourceType::Tree);

      MapFieldIndex fieldIndex = map.calcFieldIndex({ x, z });
      map.set(fieldIndex, MapFieldType::Tree);
    }
  }
}
