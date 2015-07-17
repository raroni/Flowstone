#include "Misc/Error.h"
#include "Simulation/Steering/SteeringSystem.h"
#include "Animation/Animator.h"
#include "Client/Direction/DirectionConfig.h"
#include "Client/Direction/DirectionInstanceList.h"
#include "Client/Direction/DirectionSteering.h"

namespace Client {
  namespace DirectionSteering {
    namespace InstanceList = DirectionInstanceList;

    DirectionSteeringConfig configs[DirectionConfig::groupMax] = { {
      .run = 0,
      .idle = 0
    } };

    void configureGroup(DirectionGroupIndex group, DirectionSteeringConfig config) {
      configs[group] = config;
    }

    void prepareProcess(::Database::EntityHandle entity, Animation::PoseHandle *poseHandle, const DirectionSteeringConfig **config) {
      uint16_t instanceIndex = InstanceList::getIndexByEntity(entity);
      DirectionGroupIndex group = InstanceList::getGroup(instanceIndex);
      *config = &configs[group];
      assert((*config)->run != 0 || (*config)->idle != 0);
      *poseHandle = InstanceList::getPoseHandle(instanceIndex);
    }

    void processStartEvent(const Simulation::SteeringStartEvent *event) {
      const DirectionSteeringConfig *config;
      Animation::PoseHandle poseHandle;
      prepareProcess(event->entity, &poseHandle, &config);
      Animation::Animator::changeAnimation(poseHandle, config->run);
    }

    void processStopEvent(const Simulation::SteeringStopEvent *event) {
      const DirectionSteeringConfig *config;
      Animation::PoseHandle poseHandle;
      prepareProcess(event->entity, &poseHandle, &config);
      Animation::Animator::changeAnimation(poseHandle, config->idle);
    }
  }
}
