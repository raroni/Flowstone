#include "Animation/Animator.h"
#include "Simulation/Steering/SteeringSystem.h"
#include "Client/DirectionInstanceList.h"
#include "Client/DirectionGroupList.h"
#include "Client/Direction.h"

namespace Client {
  namespace Direction {
    namespace InstanceList = DirectionInstanceList;
    namespace GroupList = DirectionGroupList;

    using namespace Database;

    void handleSteeringEvent() {

    }

    void initialize() {
      Simulation::SteeringSystem::setEventHandler(handleSteeringEvent);
    }

    DirectionInstanceHandle createInstance(DirectionGroupIndex group, Animation::PoseHandle pose, Database::EntityHandle simEntity) {
      DirectionInstanceHandle handle = InstanceList::create(group);
      DirectionGroupList::addInstance(group, pose, simEntity);
    }

    DirectionGroupIndex createGroup(uint8_t instanceMax) {
      return DirectionGroupList::create(instanceMax);
    }

    void update() {
      //Animation::Animator::changeAnimation(poseHandles[i], animation);
    }

    void prepare() {
      update();
    }
  }
}
