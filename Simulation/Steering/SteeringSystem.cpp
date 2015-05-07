#include "Physics/Engine.h"
#include "Simulation/PhysicsHack.h"
#include "Simulation/Steering/SteeringList.h"
#include "Simulation/Steering/SteeringSystem.h"

namespace Simulation {
  namespace SteeringSystem {
    using namespace Physics;
    using namespace Fixie;
    namespace List = SteeringList;
    Num tolerance = Num::inverse(32);

    void update() {
      for(uint16_t i=0; i<List::getCount(); ++i) {
        DynamicDriver driver = physicsEngine.getDynamicDriver(List::dynamicDriverHandles[i]);
        Body body = physicsEngine.getBody(driver.bodyHandle);

        Fixie::Vector3 positionDifference = List::targets[i] - (*body.position);
        if(positionDifference.calcSquaredLength() > tolerance) {
          Fixie::Vector3 direction = Vector3::normalize(positionDifference);
          (*driver.force) += direction;
        }
      }
    }

    SteeringHandle create(Physics::DynamicDriverHandle handle) {
      return List::create(handle);
    }

    Steering get(SteeringHandle handle) {
      return List::get(handle);
    }

    void destroy(SteeringHandle handle) {
      List::destroy(handle);
    }
  }
}
