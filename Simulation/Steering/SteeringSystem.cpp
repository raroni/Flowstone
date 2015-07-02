#include "Physics/Engine.h"
#include "Fixie/Geometry.h"
#include "Simulation/PhysicsHack.h"
#include "Simulation/Steering/SteeringList.h"
#include "Simulation/Steering/SteeringSystem.h"

namespace Simulation {
  namespace SteeringSystem {
    using namespace Physics;
    using namespace Fixie;
    namespace List = SteeringList;
    Num tolerance = Num::inverse(32);
    void emptyEventHandler() { }
    SteeringEventHandler eventHandler = emptyEventHandler;

    void update() {
      Vector3 forward(0, 0, 1);
      for(uint16_t i=0; i<List::getCount(); ++i) {
        DynamicDriver driver = physicsEngine.getDynamicDriver(List::dynamicDriverHandles[i]);
        Body body = physicsEngine.getBody(driver.bodyHandle);

        Vector3 positionDifference = List::targets[i] - (*body.position);
        if(positionDifference.calcSquaredLength() > tolerance) {
          Vector3 direction = Vector3::normalize(positionDifference);
          (*driver.force) += direction;
        }

        if(body.velocity->calcSquaredLength() > Num::inverse(16)) {
          Vector3 orientationDirection = Geometry::createRotated(
            &forward,
            body.orientation
          );

          Vector3 movementDirection = Vector3::normalize(*body.velocity);
          (*driver.torque) += Vector3::cross(orientationDirection, movementDirection);
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

    void setEventHandler(SteeringEventHandler func) {
      eventHandler = func;
    }
  }
}
