#include "Misc/Error.h"
#include "Animation/Animator.h"
#include "Simulation/Steering/SteeringSystem.h"
#include "Simulation/Event/EventStreamIterator.h"
#include "Client/EventSystem.h"
#include "Client/Direction/DirectionInstanceList.h"
#include "Client/Direction/DirectionConfig.h"
#include "Client/Direction/DirectionSteering.h"
#include "Client/Direction/DirectionHarvesting.h"
#include "Client/Direction/Direction.h"

namespace Client {
  namespace Direction {
    namespace InstanceList = DirectionInstanceList;
    using namespace Database;
    uint8_t groupCount = 0;
    uint8_t eventSubscriptionID;
    typedef Simulation::EventType EventType;

    void initialize() {
      EventType types[] = {
        EventType::SteeringStart,
        EventType::SteeringStop,
        EventType::HarvestWorkStart
      };
      uint8_t typeCount = sizeof(types)/sizeof(EventType);
      eventSubscriptionID = EventSystem::createSubscription(types, typeCount);
    }

    DirectionGroupIndex createGroup() {
      assert(groupCount != DirectionConfig::groupMax);
      return groupCount++;
    }

    void addSteering(DirectionGroupIndex group, DirectionSteeringConfig config) {
      DirectionSteering::configureGroup(group, config);
    }

    void addHarvesting(DirectionGroupIndex group, DirectionHarvestingConfig config) {
      DirectionHarvesting::configureGroup(group, config);
    }

    DirectionInstanceHandle createInstance(DirectionGroupIndex group, Animation::PoseHandle pose, Database::EntityHandle simEntity) {
      return InstanceList::create(group, pose, simEntity);
    }

    void update() {
      const void *stream = EventSystem::getStream(eventSubscriptionID);
      uint16_t streamLength = EventSystem::getStreamLength(eventSubscriptionID);
      Simulation::EventStreamIterator iterator;
      iterator.stream = stream;
      iterator.length = streamLength;
      while(!iterator.atEnd()) {
        EventType type = iterator.sampleType();
        switch(type) {
          case EventType::SteeringStart: {
            const Simulation::SteeringStartEvent *event = iterator.readSteeringStart();
            DirectionSteering::processStartEvent(event);
            break;
          }
          case EventType::SteeringStop: {
            const Simulation::SteeringStopEvent *event = iterator.readSteeringStop();
            DirectionSteering::processStopEvent(event);
            break;
          }
          case EventType::HarvestWorkStart: {
            const Simulation::HarvestWorkStartEvent *event = iterator.readHarvestWorkStart();
            DirectionHarvesting::processStartEvent(event);
            break;
          }
          default:
            fatalError("Unknown event.");
        }
      }
    }

    void prepare() {
      update();
    }
  }
}
