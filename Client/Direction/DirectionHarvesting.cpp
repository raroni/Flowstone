#include "Animation/Animator.h"
#include "Client/Direction/DirectionInstanceList.h"
#include "Client/Direction/DirectionHarvestingConfig.h"
#include "Client/Direction/DirectionConfig.h"
#include "Client/Direction/DirectionHarvesting.h"

namespace Client {
  namespace DirectionHarvesting {
    namespace InstanceList = DirectionInstanceList;

    DirectionHarvestingConfig configs[DirectionConfig::groupMax] = { {
      .work = 0,
      .idle = 0
    } };

    void prepareProcess(::Database::EntityHandle entity, Animation::PoseHandle *poseHandle, const DirectionHarvestingConfig **config) {
      uint16_t instanceIndex = InstanceList::getIndexByEntity(entity);
      DirectionGroupIndex group = InstanceList::getGroup(instanceIndex);
      *config = &configs[group];
      assert((*config)->work != 0 || (*config)->idle != 0);
      *poseHandle = InstanceList::getPoseHandle(instanceIndex);
    }

    void processStartEvent(const Simulation::HarvestWorkStartEvent *event) {
      const DirectionHarvestingConfig *config;
      Animation::PoseHandle poseHandle;
      prepareProcess(event->worker, &poseHandle, &config);
      Animation::Animator::changeAnimation(poseHandle, config->work);
    }

    void configureGroup(DirectionGroupIndex group, DirectionHarvestingConfig config) {
      configs[group] = config;
    }
  }
}
