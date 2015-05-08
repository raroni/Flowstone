#include <assert.h>
#include "Fixie/Num.h"
#include "Animation/Animator.h"
#include "Simulation/Database.h"
#include "Misc/HandleList.h"
#include "Client/Direction.h"

namespace Client {
  namespace Direction {
    using namespace Database;
    static const uint16_t max = 128;
    EntityHandle simEntityHandles[max];
    Animation::PoseIndex poseHandles[max];
    DirectionGroupHandle groupHandles[max];
    uint8_t animations[max];
    uint16_t indices[max];
    uint16_t handles[max];
    HandleList handleList(max, indices, handles);
    const uint8_t groupMax = 16;
    DirectionGroup groups[groupMax];
    uint8_t groupCount = 0;

    DirectionHandle create(Animation::PoseIndex poseHandle, EntityHandle simEntityHandle, DirectionGroupHandle groupHandle) {
      uint16_t index;
      DirectionHandle directionHandle;
      handleList.create(&index, &directionHandle);
      poseHandles[index] = poseHandle;
      simEntityHandles[index] = simEntityHandle;
      groupHandles[index] = groupHandle;
      animations[index] = 0;
      return directionHandle;
    }

    DirectionGroupHandle createGroup(const DirectionGroup *group) {
      assert(groupCount != groupMax);
      groups[groupCount] = *group;
      return groupCount++;
    }

    void update() {
      for(uint16_t i=0; i<handleList.getCount(); ++i) {
        uint8_t animation;
        DirectionGroup *group = &groups[groupHandles[i]];

        Physics::Body body = Simulation::Database::getBody(simEntityHandles[i]);
        if(body.velocity->calcSquaredLength() > Fixie::Num::inverse(32)) {
          animation = group->movingAnimation;
        } else {
          animation = group->idleAnimation;
        }

        if(animation != animations[i]) {
          animations[i] = animation;
          Animation::animator.changeAnimation(poseHandles[i], animation);
        }
      }
    }

    void prepare() {
      update();
    }
  }
}
