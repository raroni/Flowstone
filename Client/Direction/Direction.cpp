#include "Animation/Animator.h"
#include "Simulation/Steering/SteeringSystem.h"
#include "Client/Direction/DirectionInstanceList.h"
#include "Client/Direction/DirectionConfig.h"
#include "Client/Direction/DirectionSteering.h"
#include "Client/Direction/DirectionEventList.h"
#include "Client/Direction/Direction.h"

namespace Client {
  namespace Direction {
    namespace InstanceList = DirectionInstanceList;
    namespace EventList = DirectionEventList;
    using namespace Database;

    uint8_t groupCount = 0;

    void initialize() {
      DirectionSteering::initialize();
    }

    DirectionGroupIndex createGroup() {
      assert(groupCount != DirectionConfig::groupMax);
      return groupCount++;
    }

    void addSteering(DirectionGroupIndex group, DirectionSteeringConfig config) {
      DirectionSteering::configureGroup(group, config);
    }

    DirectionInstanceHandle createInstance(DirectionGroupIndex group, Animation::PoseHandle pose, Database::EntityHandle simEntity) {
      return InstanceList::create(group, pose, simEntity);
    }

    void update() {
      for(uint16_t i=0; i<EventList::getCount(); ++i) {
        const DirectionEvent *event = EventList::get(i);
        switch(event->type) {
          case DirectionEventType::SteeringStart:
            DirectionSteering::processStartEvent(event);
            break;
          case DirectionEventType::SteeringStop:
            DirectionSteering::processStopEvent(event);
            break;
          default:
            fatalError("Unknown direction event.");
        }
      }
      EventList::clear();
    }

    void prepare() {
      update();
    }
  }
}
