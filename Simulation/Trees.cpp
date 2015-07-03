#include "Database/EntityHandle.h"
#include "Simulation/Harvest/HarvestEvent.h"
#include "Simulation/Harvest/HarvestEventList.h"
#include "Simulation/Database.h"
#include "Simulation/Pathfinding/Map.h"
#include "Simulation/Pathfinding/MapFieldIndex.h"
#include "Simulation/Pathfinding/MapFieldType.h"
#include "Simulation/Trees.h"

namespace Simulation {
  namespace Trees {
    void create(uint16_t x, uint16_t z) {
      ::Database::EntityHandle tree = Database::createEntity();

      Database::createBody(tree);
      Physics::Body body = Database::getBody(tree);
      (*body.position)[0] = x;
      (*body.position)[2] = z;

      Database::createSphereCollider(tree, Fixie::Num(0.25), Physics::ColliderType::Static);

      Database::createHarvestResource(tree, HarvestResourceType::Tree);

      Database::createTicketTarget(tree);

      MapFieldIndex fieldIndex = map.calcFieldIndex({ x, z });
      map.set(fieldIndex, MapFieldType::Tree);
    }

    void processHarvestCompletionEvent(const HarvestEvent *event) {
      ::Database::EntityHandle tree = event->resource;
      Database::destroyHarvestResource(tree);
      Database::destroyTicketTarget(tree);

      Physics::Body body = Database::getBody(tree);
      Fixie::Vector3 position = *body.position;
      MapFieldIndex fieldIndex = map.calcFieldIndex({ position[0], position[2] });
      map.set(fieldIndex, MapFieldType::Grass);
    }

    void update() {
      uint16_t eventCount = HarvestEventList::getCount();
      for(uint16_t i=0; i<eventCount; ++i) {
        const HarvestEvent *event = HarvestEventList::get(i);
        switch(event->type) {
          case HarvestEventType::Completion:
            processHarvestCompletionEvent(event);
            break;
        }
      }
    }
  }
}
