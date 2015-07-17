#include "Misc/Error.h"
#include "Simulation/Steering/SteeringSystem.h"
#include "Animation/Animator.h"
#include "Client/Direction/DirectionConfig.h"
#include "Client/Direction/DirectionInstanceList.h"
#include "Client/Direction/DirectionEventList.h"
#include "Client/Direction/DirectionSteering.h"

namespace Client {
  namespace DirectionSteering {
    namespace InstanceList = DirectionInstanceList;
    namespace EventList = DirectionEventList;

    DirectionSteeringConfig configs[DirectionConfig::groupMax] = { {
      .run = 0,
      .idle = 0
    } };

    void storeEvent(const Simulation::SteeringEvent *steeringEvent) {
      switch(steeringEvent->type) {
        case Simulation::SteeringEventType::Start: {
          DirectionEvent event;
          event.type = DirectionEventType::SteeringStart;
          event.entity = steeringEvent->entity;
          EventList::add(&event);
          break;
        }
        case Simulation::SteeringEventType::Stop: {
          DirectionEvent event;
          event.type = DirectionEventType::SteeringStop;
          event.entity = steeringEvent->entity;
          EventList::add(&event);
          break;
        }
        default:
          fatalError("Unknown steering event type.");
      }
    }

    void configureGroup(DirectionGroupIndex group, DirectionSteeringConfig config) {
      configs[group] = config;
    }

    void initialize() {
      //This will soon be replaced by a new direction system
      //For now, we'll just out-comment this so it doesn't interfere.
      //Simulation::SteeringSystem::setEventHandler(storeEvent);
    }

    void prepareProcess(const DirectionEvent *event, Animation::PoseHandle *poseHandle, const DirectionSteeringConfig **config) {
      uint16_t instanceIndex = InstanceList::getIndexByEntity(event->entity);
      DirectionGroupIndex group = InstanceList::getGroup(instanceIndex);
      *config = &configs[group];
      assert((*config)->run != 0 || (*config)->idle != 0);
      *poseHandle = InstanceList::getPoseHandle(instanceIndex);
    }

    void processStartEvent(const DirectionEvent *event) {
      const DirectionSteeringConfig *config;
      Animation::PoseHandle poseHandle;
      prepareProcess(event, &poseHandle, &config);
      Animation::Animator::changeAnimation(poseHandle, config->run);
    }

    void processStopEvent(const DirectionEvent *event) {
      const DirectionSteeringConfig *config;
      Animation::PoseHandle poseHandle;
      prepareProcess(event, &poseHandle, &config);
      Animation::Animator::changeAnimation(poseHandle, config->idle);
    }
  }
}
