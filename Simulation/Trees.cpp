#include "Database/EntityHandle.h"
#include "Simulation/Event/EventSystem.h"
#include "Simulation/Event/EventType.h"
#include "Simulation/Event/HarvestCompletionEvent.h"
#include "Simulation/Database.h"
#include "Simulation/Pathfinding/Map.h"
#include "Simulation/Pathfinding/MapFieldIndex.h"
#include "Simulation/Pathfinding/MapFieldType.h"
#include "Simulation/Trees.h"

namespace Simulation {
  namespace Trees {
    uint8_t eventSubscriptionID;

    void initialize() {
      EventType types[] = {
        EventType::HarvestCompletion
      };
      uint8_t typeCount = sizeof(types)/sizeof(EventType);
      eventSubscriptionID = EventSystem::createSubscription(types, typeCount);
    }

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

    void processHarvestCompletionEvent(const HarvestCompletionEvent *event) {
      ::Database::EntityHandle tree = event->resource;
      Database::destroyHarvestResource(tree);
      Database::destroyTicketTarget(tree);

      Physics::Body body = Database::getBody(tree);
      Fixie::Vector3 position = *body.position;
      MapFieldIndex fieldIndex = map.calcFieldIndex({ position[0], position[2] });
      map.set(fieldIndex, MapFieldType::Grass);
    }

    void update() {
      const void *stream = EventSystem::getEventStream(eventSubscriptionID);
      const HarvestCompletionEvent *events = static_cast<const HarvestCompletionEvent*>(stream);
      uint16_t streamLength = EventSystem::getEventStreamLength(eventSubscriptionID);
      uint16_t count = streamLength/sizeof(HarvestCompletionEvent);

      for(uint16_t i=0; i<count; ++i) {
        processHarvestCompletionEvent(events+i);
      }
    }
  }
}
